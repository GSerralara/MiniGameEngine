#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../Component.h"
#include "../AssetManager.h"
#include "../TextureManager.h"
#include "./TransformComponent.h"
#include "../Animation.h"

#include <SDL2/SDL.h>
class SpriteComponent: public Component{
	private:
		TransformComponent* transfrom;
		SDL_Texture* texture;
		SDL_Rect sourceRectangle;
		SDL_Rect destinationRectangle;
		/*For animated Sprites*/
		bool animated;
		bool fixed;
		int frames;
		int animationSpeed;
		std::map<std::string, Animation> animations;
		unsigned int animationIndex = 0;
		std::string currentAnimationName;
	public:
		
		
		SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
		SpriteComponent(const char* filepath) {
			this->animated = false;
			this->fixed = false;
			setTexture(filepath);
		}
		SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {
			this->animated = true;
			this->frames = numFrames;
			this->animationSpeed = animationSpeed;
			this->fixed = isFixed;

			if (hasDirections) {
				Animation downAnimation = Animation(0, numFrames, animationSpeed);
				Animation rightAnimation = Animation(1, numFrames, animationSpeed);
				Animation leftAnimation = Animation(2, numFrames, animationSpeed);
				Animation upAnimation = Animation(3, numFrames, animationSpeed);
				animations.emplace("DownAnimation", downAnimation);
				animations.emplace("RightAnimation", rightAnimation);
				animations.emplace("LeftAnimation", leftAnimation);
				animations.emplace("UpAnimation", upAnimation);
				this->animationIndex = 0;
				this->currentAnimationName = "DownAnimation";
			}
			else {
				Animation singleAnimation = Animation(0, numFrames, animationSpeed);
				animations.emplace("SingleAnimation", singleAnimation);
				this->animationIndex = 0;
				this->currentAnimationName = "SingleAnimation";
			}
			Play(this->currentAnimationName);
			setTexture(id);
		}
		~SpriteComponent() {

		}

		void Play(std::string animationName) {
			frames = animations[animationName].frames;
			animationIndex = animations[animationName].index;
			animationSpeed = animations[animationName].animationSpeed;
			currentAnimationName = animationName;
		}
		void setTexture(std::string assetTextureId) {
			texture = Game::assetManager->getTexture(assetTextureId);
		}
		void Initialize() override {
			transfrom = owner->getComponent<TransformComponent>();
			sourceRectangle.x = 0;
			sourceRectangle.y = 0;
			sourceRectangle.w = transfrom->width;
			sourceRectangle.h = transfrom->height;
		}
		void Update(float deltaTime) override {
			if (animated) {
				sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % frames);
			}
			sourceRectangle.y = animationIndex * transfrom->height;

			destinationRectangle.x = (int)transfrom->position.x;
			destinationRectangle.y = (int)transfrom->position.y;
			destinationRectangle.w = transfrom->width*transfrom->scale;
			destinationRectangle.h = transfrom->height*transfrom->scale;
		}
		void Render() override {
			TextureManager::draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
		}
	
};

#endif // !SPRITECOMPONENT_H


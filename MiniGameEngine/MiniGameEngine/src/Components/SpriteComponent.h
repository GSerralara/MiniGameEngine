#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../Component.h"
#include "../AssetManager.h"
#include "../TextureManager.h"
#include "./TransformComponent.h"

#include <SDL2/SDL.h>
class SpriteComponent: public Component{
	private:
		TransformComponent* transfrom;
		SDL_Texture* texture;
		SDL_Rect sourceRectangle;
		SDL_Rect destinationRectangle;
	public:
		
		
		SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
		SpriteComponent(const char* filepath) {
			setTexture(filepath);
		}
		~SpriteComponent() {

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


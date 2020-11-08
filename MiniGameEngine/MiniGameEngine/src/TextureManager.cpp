#include "TextureManager.h"
TextureManager::TextureManager() {

}
TextureManager::~TextureManager() {

}
SDL_Texture* TextureManager::LoadTexture(const char* filename) {
	SDL_Surface* surface = IMG_Load(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}
void TextureManager::draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::renderer, texture, 
		&sourceRectangle, &destinationRectangle, 0.0, NULL, flip);

}

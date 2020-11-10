#include "TextureManager.h"
#include <iostream>
#include <SDL2_image/SDL_image.h>

TextureManager::TextureManager() {

}
TextureManager::~TextureManager() {

}
SDL_Texture* TextureManager::LoadTexture(const char* filename) {
	
	SDL_Surface* surface = SDL_LoadBMP(filename);//IMG_Load(filename);
	if (surface == nullptr) {
		std::cout << "IMG_Load: " << IMG_GetError() << "\n";
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}
void TextureManager::draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::renderer, texture, 
		&sourceRectangle, &destinationRectangle, 0.0, NULL, flip);

}

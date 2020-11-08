#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Game.h"

class TextureManager
{	
public:
	TextureManager();
	~TextureManager();
	static SDL_Texture* LoadTexture(const char* filename);
	static void draw(SDL_Texture* texture, SDL_Rect sourceRectangle, 
		SDL_Rect destinationRectangle, SDL_RendererFlip flip);
};
#endif
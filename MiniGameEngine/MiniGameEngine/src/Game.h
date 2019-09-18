#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
class Game
{
public:
	bool isRunning;
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	Game();
	~Game();
	void initialize(int width, int heigh);
	void processInput();
	void update();
	void render();
	void destroy();
};
#include <iostream>
#include "Game.h"

Game::Game() {
	this->isRunning =  false;
}
Game::~Game() {
	
}

void Game::initialize(int width,int heigh) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error initializing SDL" << std::endl;
		return;
	}
	this->window = SDL_CreateWindow(NULL, //window name
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, // win location in screen
		width, heigh, //dim
		SDL_WINDOW_BORDERLESS);//flag
	if (!window) {
		std::cerr << "Error creating SDL window" << std::endl;
		return;
	}
	renderer = SDL_CreateRenderer(window, //window where rendering is displayed
	-1, //-1 to initialize the first one supporting the requested flags
	0);//no warning
	if (!renderer) {
		std::cerr << "Error creating SDL renderer" << std::endl;
		return;
	}
	isRunning = true;
}
void Game::processInput() {
	SDL_Event event;//create an event container
	SDL_PollEvent(&event);//pull the event it's happening
	//process data based on a event
	switch (event.type)
	{
	case SDL_QUIT: {//case of ESC button
		isRunning = false;
		break;
	}
	case SDL_KEYDOWN:{
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			isRunning = false;
		}
	}
	default:
		break;
	}
}
void Game::update() {

}
void Game::render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void Game::destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

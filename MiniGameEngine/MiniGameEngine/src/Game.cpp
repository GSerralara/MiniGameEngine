#include <iostream>
#include <filesystem>
#include <experimental/filesystem>
#include "Constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "GLM/glm.hpp"

namespace fs = std::experimental::filesystem::v1;

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {
}

bool Game::IsRunning() const {
    return this->isRunning;
}

void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    LoadLevel(0);

    isRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber) {
	fs::path p = fs::current_path();
	p.append("\\..\\MiniGameEngine\\Assets\\images\\start.png");
	fs::path p2 = fs::current_path();
	p2.append("\\..\\MiniGameEngine\\Assets\\images\\chopper-spritesheet.png");
	fs::path p3 = fs::current_path();
	p3.append("\\..\\MiniGameEngine\\Assets\\images\\radar.png");

	//start including new assets to the assetManager list
	assetManager->addTexture("start", p.u8string().c_str());
	assetManager->addTexture("chopper", p2.u8string().c_str());
	assetManager->addTexture("radar", p3.u8string().c_str());
	//start including entities and components to them
    Entity& newEntity(manager.AddEntity("projectile"));
    newEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
	newEntity.AddComponent<SpriteComponent>("start");

	Entity& chopperEntity(manager.AddEntity("chopper"));
	chopperEntity.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
	chopperEntity.AddComponent<SpriteComponent>("chopper", 2, 90, true, false);

	Entity& radarEntity(manager.AddEntity("radar"));
	radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	radarEntity.AddComponent<SpriteComponent>("radar", 8, 150, false, true);
}

void Game::ProcessInput() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
        }
        default: {
            break;
        }
    }
}

void Game::Update() {
    // Wait until 16ms has ellapsed since the last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
    
    // Delta time is the difference in ticks from last frame converted to secomds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.HasNoEntities()) {
        return;
    }

    manager.Render(); 

    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

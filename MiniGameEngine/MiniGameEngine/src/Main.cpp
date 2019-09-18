#include <iostream>
#include "Game.h"
#include "Constants.h"

//change to main() when it's posible
int wmain() {
	Game *game = new Game();

	game->initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

	while (game->isRunning) {
		game->processInput();
		game->update();
		game->render();
	}
	game->destroy();
	return 0;
}
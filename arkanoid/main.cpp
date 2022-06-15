#include "game.h"

int main() {
	Game game;
	if (game.run())
		return 0;
	else return -1;
}
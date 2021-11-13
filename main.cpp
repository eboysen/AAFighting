#include "game.h"
#undef main
int main() {
	game Game = game();
	

	while (Game.active) {
		Game.update();
		Game.render();
	}
	return 0;
}
#include "game.h"
#undef main
int main() {
	game Game = game(1200, 600);
	
	while (Game.active) {
		Game.update();
		Game.render();
	}
	return 0;
}
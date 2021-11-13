#include <SDL.h>
#undef main
int main() {
		SDL_Window * window = SDL_CreateWindow("AAFighter", 200, 200, 400, 600, SDL_WINDOW_OPENGL);
		while (true) {
			SDL_Event event;
			if (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					break;
				}
			}
		}

		SDL_DestroyWindow(window);
		SDL_Quit();

		return 0;
}
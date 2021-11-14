#include "game.h"

const double FIXED_UPDATE_TIME = 0.02;

game::game(Uint16 width, Uint16 height) {
	game::active = true;
	game::window_width = width;
	game::window_height = height;
	game::window = SDL_CreateWindow("AAFighter", 100, 100, width, height, SDL_WINDOW_OPENGL);
	game::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	entitySet set1 = entitySet("./assets/playerWalk.png", 5, 0.1);
	entitySet set2 = entitySet("./assets/seaworld.png", 10, 0.1);
	game::player = entity::entity(renderer, set1, width * 0.2, height * 0.8);
	game::enemy = entity::entity(renderer, set2, width * 0.8, height * 0.8);
	game::enemyBrain;
	game::now = SDL_GetPerformanceCounter();
	game::environment = environment::environment(renderer);
	game::weather;
	for (int i = 0; i < 250; i++) {
		int x = rand() % width;
		int y = rand() % height;
		rain newRain = rain(x, y, height);
		weather.push_back(newRain);
	}
}

game::~game() {
	SDL_DestroyRenderer(game::renderer);
	SDL_DestroyWindow(game::window);
	SDL_Quit();
}

void game::update() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			active = false;
			return;
		}
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				player.input(player.Left, true);
				break;
			case SDLK_RIGHT:
				player.input(player.Right, true);
				break;
			case SDLK_UP:
				player.input(player.Up, true);
				break;
			case SDLK_DOWN:
				player.input(player.Down, true);
				break;
			case SDLK_SPACE:
				player.input(player.Jump, true);
				break;
			case SDLK_x:
				player.input(player.Dash, true);
				break;
			case SDLK_z:
				player.input(player.Attack, true);
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				player.input(player.Left, false);
				break;
			case SDLK_RIGHT:
				player.input(player.Right, false);
				break;
			case SDLK_UP:
				player.input(player.Up, false);
				break;
			case SDLK_DOWN:
				player.input(player.Down, false);
				break;
			case SDLK_SPACE:
				player.input(player.Jump, false);
				break;
			case SDLK_x:
				player.input(player.Dash, false);
				break;
			case SDLK_z:
				player.input(player.Attack, false);
				break;
			}
			break;
		}
	}
	last = now;
	now = SDL_GetPerformanceCounter();
	double deltaTime = ((now - last) / (double)SDL_GetPerformanceFrequency());

	currentTime += deltaTime;
	while (currentTime > FIXED_UPDATE_TIME) {
		currentTime -= FIXED_UPDATE_TIME;
		player.fixedUpdate();
		player.collide(window_width, window_height);
		environment.platformCheck(&player);
		enemy.fixedUpdate();
		enemy.collide(window_width, window_height);
		environment.platformCheck(&enemy);
	}

	player.update(deltaTime);
	if (player.isAttacking()) {
		vector2 kickback = player.attack(enemy.getHitbox());
		enemy.applyKickback(kickback.x, kickback.y);
	}
	enemy.update(deltaTime);
	//enemy.think(&(player));

	for (int i = 0; i < weather.size(); i++) {
		weather.at(i).update(deltaTime);
	}
	environment.platformCheck(& player);
}

void game::render() {
	SDL_SetRenderDrawColor(renderer, 46, 51, 61, 255);
	SDL_RenderClear(renderer);
	for (int i = 0; i < weather.size(); i++) {
		weather.at(i).render(renderer);
	}
	environment.renderEnvironment(renderer,window_width,window_height);
	enemy.render(renderer);
	player.render(renderer);
	
	SDL_RenderPresent(renderer);
}


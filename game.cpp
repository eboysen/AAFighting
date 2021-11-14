#include "game.h"

const double FIXED_UPDATE_TIME = 0.02;

// ---------------- CONSTRUCTOR -----------------

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
	int center = window_width / 2;
	qRect.x = center - 64;
	qRect.y = 350;
	qRect.h = 128;
	qRect.w = 128;
	qTex = TextureManager::loadTexture("./assets/quit.png", renderer);
	pRect.x = center - 64;
	pRect.y = 200;
	pRect.h = 128;
	pRect.w = 128;
	pTex = TextureManager::loadTexture("./assets/play.png", renderer);

	AARect.w = 64;
	AARect.h = 64;
	AARect.x = center - 100;
	AARect.y = 200;

	SeaRect.w = 64;
	SeaRect.h = 64;
	SeaRect.x = center + 36;
	SeaRect.y = 200;

	playerSelectionRect.w = 70;
	playerSelectionRect.h = 70;
	playerSelectionRect.x = AARect.x - 3;
	playerSelectionRect.y = AARect.y - 3;

	alphaRect.w = 64;
	alphaRect.h = 64;
	alphaRect.x = center - 100;
	alphaRect.y = 280;

	omegaRect.w = 64;
	omegaRect.h = 64;
	omegaRect.x = center + 36;
	omegaRect.y = 280;

	levelSelectionRect.w = 70;
	levelSelectionRect.h = 70;
	levelSelectionRect.x = alphaRect.x - 3;
	levelSelectionRect.y = alphaRect.y - 3;

	charRect.w = 32;
	charRect.h = 32;
	charRect.x = 0;
	charRect.y = 0;

	arrowRect.w = 64;
	arrowRect.h = 64;
	arrowRect.x = window_width - 80;
	arrowRect.y = window_height - 80;

	AATex = TextureManager::loadTexture("./assets/playerWalk.png", renderer);
	SeaTex = TextureManager::loadTexture("./assets/seaworld.png", renderer);
	alphaTex = TextureManager::loadTexture("./assets/alpha.png", renderer);
	omegaTex = TextureManager::loadTexture("./assets/omega.png", renderer);
	arrowTex = TextureManager::loadTexture("./assets/arrow.png", renderer);
	game::weather;
	for (int i = 0; i < 250; i++) {
		int x = rand() % width;
		int y = rand() % height;
		rain newRain = rain(x, y, height);
		weather.push_back(newRain);
	}
	SDL_Rect healthBarRect = SDL_Rect();
	double w = width / 4;
	healthBarRect.x = 40;
	healthBarRect.y = 40;
	healthBarRect.w = w;
	healthBarRect.h = 40;
	game::playerHealth = healthBar(renderer, healthBarRect, 100, true);
	healthBarRect.x = width - w - 40;
	game::enemyHealth = healthBar(renderer, healthBarRect, 100, false);
}

// -------------------- MENU --------------------

void game::menuUpdate() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			menuActive = false;
			active = false;
			return;
		}
		switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			SDL_Point mousePos = { event.button.x,event.button.y };
			if (SDL_PointInRect(&mousePos, &pRect) && startMenu) {
				startMenu = false;
			}
			else if (SDL_PointInRect(&mousePos, &qRect) && startMenu) {
				menuActive = false;
				active = false;
			}
			else if (SDL_PointInRect(&mousePos, &AARect) && !startMenu) {
				playerSelect = "AA";
				playerSelectionRect.x = AARect.x - 3;
				playerSelectionRect.y = AARect.y - 3;
			}
			else if (SDL_PointInRect(&mousePos, &SeaRect) && !startMenu) {
				playerSelect = "Sea";
				playerSelectionRect.x = SeaRect.x - 3;
				playerSelectionRect.y = SeaRect.y - 3;
			}
			else if (SDL_PointInRect(&mousePos, &alphaRect) && !startMenu) {
				lvlSelect = "alpha";
				levelSelectionRect.x = alphaRect.x - 3;
				levelSelectionRect.y = alphaRect.y - 3;
			}
			else if (SDL_PointInRect(&mousePos, &omegaRect) && !startMenu) {
				lvlSelect = "omega";
				levelSelectionRect.x = omegaRect.x - 3;
				levelSelectionRect.y = omegaRect.y - 3;
			}
			else if (SDL_PointInRect(&mousePos, &arrowRect) && !startMenu) {
				characterSelect = false;
				menuActive = false;
				if (lvlSelect == "alpha") {
					environment.setLevel(1);
				}
				if (lvlSelect == "omega") {
					environment.setLevel(0);
				}
				environment.renderEnvironment(renderer, window_width, window_height);
				entitySet set1 = entitySet("./assets/playerWalk.png", 5, 0.1);
				entitySet set2 = entitySet("./assets/seaworld.png", 10, 0.1);
				if (playerSelect == "AA") {
					game::player = entity::entity(renderer, set1, window_width * 0.2, window_height * 0.8);
					game::enemy = entity::entity(renderer, set2, window_width * 0.8, window_height * 0.8);
				}
				else {
					game::player = entity::entity(renderer, set2, window_width * 0.2, window_height * 0.8);
					game::enemy = entity::entity(renderer, set1, window_width * 0.8, window_height * 0.8);
				}
			}
			break;

		}
	}
}

void game::menuRender() {
	SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);
	SDL_RenderClear(renderer);
	if (startMenu) {
		SDL_RenderCopy(renderer, pTex, NULL, &pRect);
		SDL_RenderCopy(renderer, qTex, NULL, &qRect);
	}
	else if (characterSelect) {
		SDL_RenderCopy(renderer, AATex, &charRect, &AARect);
		SDL_RenderCopy(renderer, SeaTex, &charRect, &SeaRect);
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderDrawRect(renderer, &playerSelectionRect);
		SDL_RenderCopy(renderer, alphaTex, NULL, &alphaRect);
		SDL_RenderCopy(renderer, omegaTex, NULL, &omegaRect);
		SDL_RenderDrawRect(renderer, &levelSelectionRect);
		SDL_RenderCopy(renderer, arrowTex, NULL, &arrowRect);
	}
	SDL_RenderPresent(renderer);
}

// -------------------- GAME --------------------

void game::update() {
	enemyBrain.think(&enemy, &player);

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
		if (kickback.x != 0 && kickback.y != 0) {
			enemy.applyKickback(kickback.x, kickback.y);
		}
	}
	enemy.update(deltaTime);
	if (enemy.isAttacking()) {
		vector2 kickback = enemy.attack(player.getHitbox());
		if (kickback.x != 0 && kickback.y != 0) {
			player.applyKickback(kickback.x, kickback.y);
		}
	}

	for (int i = 0; i < weather.size(); i++) {
		weather.at(i).update(deltaTime);
	}
	environment.platformCheck(& player);

	playerHealth.setHealth(player.getHealth());
	enemyHealth.setHealth(enemy.getHealth());
	playerHealth.update(deltaTime);
	enemyHealth.update(deltaTime);

	if (player.getHealth() <= 0) {
		// LOSE
		player.kill();
		enemy.lock();
		gameOver = true;
		victory = false;
	}
	else if (enemy.getHealth() <= 0) {
		// WIN
		player.lock();
		enemy.kill();
		gameOver = true;
		victory = false;
	}
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
	
	playerHealth.render(renderer);
	enemyHealth.render(renderer);
	if (gameOver) {
		SDL_Rect endRect = SDL_Rect();
		endRect.x = window_width / 4;
		endRect.y = 3 * window_width / 4;
		endRect.w = window_width / 2;
		endRect.h = window_width / 2;
		if (victory) {
			auto win = TextureManager::loadTexture("./assets/victory.png", renderer);
			SDL_RenderCopy(renderer, win, NULL, &endRect);
		}
		else {
			auto lose = TextureManager::loadTexture("./assets/lose.png", renderer);
			SDL_RenderCopy(renderer, lose, NULL, &endRect);
		}
	}
	SDL_RenderPresent(renderer);
}

game::~game() {
	SDL_DestroyRenderer(game::renderer);
	SDL_DestroyWindow(game::window);
	SDL_Quit();
}
#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "environment.h"
#include "rain.h"
#include "entitySet.h"
#include "entity.h"
#include "enemyBrain.h"
#include "healthBar.h"

class game
{
public:
	bool active;
	bool menuActive=true;
	bool startMenu=true;
	bool characterSelect = true;
	game(Uint16 width, Uint16 height);
	~game();
	void update();
	void render();
	void menuUpdate();
	void menuRender();
	void startRain();

private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	Uint16 window_width;
	Uint16 window_height;
	Uint64 now;
	Uint64 last = 0;
	double currentTime = 0;
	environment environment;
	entity player;
	entity enemy;
	enemyBrain enemyBrain;
	std::string playerSelect = "AA";
	std::string lvlSelect = "alpha";
	std::vector<rain> weather;
	SDL_Rect qRect;
	SDL_Rect pRect;
	SDL_Rect playerSelectionRect;
	SDL_Rect AARect;
	SDL_Rect SeaRect;
	SDL_Rect alphaRect;
	SDL_Rect omegaRect;
	SDL_Rect levelSelectionRect;
	SDL_Rect charRect;
	SDL_Rect arrowRect;
	SDL_Texture* qTex;
	SDL_Texture* pTex;
	SDL_Texture* AATex;
	SDL_Texture* SeaTex;
	SDL_Texture* alphaTex;
	SDL_Texture* omegaTex;
	SDL_Texture* arrowTex;
	healthBar playerHealth;
	healthBar enemyHealth;
	bool gameOver = false;
	bool victory = false;
};


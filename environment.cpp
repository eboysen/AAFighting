#include "environment.h"
#include <SDL_image.h>
#include <iostream>
#include "TextureManager.h"
#include <vector>
int XTILE = 25;
int YTILE = 25;
int WIDTH = 600 / 25;
int HEIGHT = 600 / 25;

int lvl1[25][25] =
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5}
};
struct position {
	int y;
	int x;
};
std::vector<position> platformTiles;

environment::environment() {
}
environment::~environment() {

}

void environment::renderEnvironment(SDL_Renderer* render, int width, int height) {
	HEIGHT = height;
	WIDTH = width;
	SDL_Texture* leftCloud = TextureManager::loadTexture("./assets/leftClou.png", render);
	SDL_Texture* middleCloud = TextureManager::loadTexture("./assets/middleCloud.png", render);
	SDL_Texture* rightCloud = TextureManager::loadTexture("./assets/rightCloud.png", render);

	platformTiles.clear();


	SDL_Rect rect,srect;
	int size = width / 25;
	srect.h = 32;
	srect.w = 32;
	srect.x = 0;
	srect.y = 0;
	rect.h = size;
	rect.w = size;
	for (int x = 0; x < YTILE; x++) {
		for (int y = 0; y < XTILE; y++) {
			rect.x = x * size;
			rect.y = y * size;
			if (lvl1[y][x]%2 == 1) {
				SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
				position Platform;
				Platform.y = y;
				Platform.x = x;
				platformTiles.push_back(Platform);
				if (lvl1[y][x] == 1) {
					//std::cout << x << y << std::endl;
					SDL_RenderCopy(render, leftCloud, &srect, &rect);				
				}
				else if (lvl1[y][x] == 3) {
					//std::cout << x << y << std::endl;
					SDL_RenderCopy(render, middleCloud, &srect, &rect);
				}
				else if (lvl1[y][x] == 5) {
					//std::cout << x << y << std::endl;
					SDL_RenderCopy(render, rightCloud, &srect, &rect);
				}
			}
			else {
				SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
				SDL_RenderDrawRect(render, &rect);
			}
			
		}
	}


}

void environment::platformCheck(character* Character) {
	int size = WIDTH / 25;
	for (int y = 0; y < platformTiles.size(); y++) {
		if (Character->isFalling() &&
			Character->getY() > (double)platformTiles.at(y).y * size &&
			Character->getY() < ((double)platformTiles.at(y).y + 1) * size) {
			// Right corner character to left corner tile
			if (Character->getX() + Character->getW() > (double)platformTiles.at(y).x * size &&
				Character->getX() < (double)platformTiles.at(y).x * size) {
				environment::characterCollided(Character, (double)platformTiles.at(y).y * size);
			}
			// Left corner character to right corner tile
			else if (Character->getX() < (double)platformTiles.at(y).x * size + size &&
				Character->getX() + Character->getW() > (double)platformTiles.at(y).x * size + size) {
				environment::characterCollided(Character, (double)platformTiles.at(y).y * size);
			}
		}
	}
}

void environment::characterCollided(character* Character, double yPos) {
	Character->setPlatform(yPos);
}
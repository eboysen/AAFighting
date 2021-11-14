#pragma once
#include <stdlib.h>

#include "SDL.h"

class rain
{
public:
	rain();
	rain(int x, int y, int h);
	void update(double deltaTime);
	void render(SDL_Renderer* renderer);
private:
	int x;
	double y;
	double ys;
	int h;
	int b;
	SDL_Rect rect;
};


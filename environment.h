#pragma once
#include <SDL.h>
class environment
{
public:
	environment(int lvl1[20][25]);
	~environment();
	void renderEnvironment(SDL_Renderer * render);


};


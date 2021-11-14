#pragma once
#include <SDL_image.h>
#include <SDL.h>
class TextureManager

{
public:
	static SDL_Texture* loadTexture(const char* filename, SDL_Renderer * render);
};


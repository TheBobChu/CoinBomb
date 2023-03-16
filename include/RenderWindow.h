#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../include/Entity.h"

class RenderWindow {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	RenderWindow(const char* title, int w, int h);
	SDL_Texture* LoadTexture(const char* filePath);
	void CleanUp();
	void Clear();
	void Render(Entity& entity, int dstW, int dstH);
	void RenderHealth(SDL_Texture* texture, SDL_Rect& rect);
	void RenderText(int x, int y, const char* text, TTF_Font* font, SDL_Color color);
	void Display();
};
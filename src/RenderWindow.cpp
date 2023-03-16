#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

#include "../include/RenderWindow.h"
#include "../include/Entity.h"

RenderWindow::RenderWindow(const char* title, int w, int h)
	: window(NULL), renderer(NULL) {
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	if (window == NULL)
		std::cout << "Error: " << SDL_GetError() << std::endl;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* RenderWindow::LoadTexture(const char* filePath) {
	SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
	if (texture == NULL)
		std::cout << "Error: " << SDL_GetError() << std::endl;
	return texture;
}

void RenderWindow::CleanUp() {
	SDL_DestroyWindow(window);
}

void RenderWindow::Clear() {
	SDL_RenderClear(renderer);
}

void RenderWindow::Render(Entity& entity, int dstW, int dstH) {
	int x = entity.GetPos().x;
	int y = entity.GetPos().y;
	if (dstW == 128 && dstH == 128) {
		x -= 48;
		y -= 48;
	}
	SDL_Rect src = { entity.GetRect().x, entity.GetRect().y, entity.GetRect().w, entity.GetRect().h };
	SDL_Rect dst = { x, y, dstW, dstH };
	if (entity.GetVelX() >= 0)
		SDL_RenderCopy(renderer, entity.GetTexture(), &src, &dst);
	else
		SDL_RenderCopyEx(renderer, entity.GetTexture(), &src, &dst, 0, NULL, SDL_FLIP_HORIZONTAL);
}

void RenderWindow::RenderHealth(SDL_Texture* texture, SDL_Rect& rect) {
	SDL_Rect src = { rect.x, rect.y, rect.w, rect.h };
	SDL_Rect dst = { 38, 40, 102, 18 };
	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void RenderWindow::RenderText(int x, int y, const char* text, TTF_Font* font, SDL_Color color) {
	SDL_Surface* textSurf = TTF_RenderText_Blended(font, text, color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurf);
	SDL_Rect src = { 0, 0, textSurf->w, textSurf->h };
	SDL_Rect dst = { x, y, src.w, src.h };

	SDL_RenderCopy(renderer, textTexture, &src, &dst);
	SDL_FreeSurface(textSurf);
	SDL_DestroyTexture(textTexture);
}

void RenderWindow::Display() {
	SDL_RenderPresent(renderer);
}
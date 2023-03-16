#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.h"

class Entity {
protected:
	int velX, velY;
	Vector2f pos;
	SDL_Texture* texture;
	SDL_Rect rect;
public:
	Entity(Vector2f pos, SDL_Texture* texture, SDL_Rect rect);
	bool IsColliding(int x, int y, SDL_Rect me, SDL_Rect other);
	SDL_Rect GetBounds();
	SDL_Rect GetBlastBounds();
	virtual void Tick();

	Vector2f& GetPos();
	SDL_Texture* GetTexture();
	SDL_Rect& GetRect();
	void SetVelX(int velX);
	void SetVelY(int velY);
	int GetVelX();
	int GetVelY();
};
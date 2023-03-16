#pragma once
#include <vector>

#include "../include/Entity.h"

class Bomb : public Entity {
public:
	Bomb(Vector2f pos, SDL_Texture* texture, SDL_Rect rect);
	void Tick() override;
};
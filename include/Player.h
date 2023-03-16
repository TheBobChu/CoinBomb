#pragma once
#include <vector>

#include "../include/Entity.h"

class Player : public Entity {
private:
	int health, score, healthCooldown;
public:
	Player(Vector2f pos, SDL_Texture* texture, SDL_Rect rect);
	void Tick() override;
	void Collision(std::vector<Entity>& walls, std::vector<Entity>& coins, std::vector<Entity>& explosions);
	
	void SetHealth(int health);
	int GetHealth();
	void SetScore(int score);
	int GetScore();

	bool up, down, left, right;
};
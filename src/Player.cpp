#include "../include/Player.h"

Player::Player(Vector2f pos, SDL_Texture* texture, SDL_Rect rect)
	: Entity(pos, texture, rect) {
	health = 5;
	score = 0;
	healthCooldown = 0;
}

void Player::Tick() {
	pos.x += velX;
	pos.y += velY;

	if (up) velY = -2;
	else if (!down) velY = 0;
	if (down) velY = 2;
	else if (!up) velY = 0;
	if (left) velX = -2;
	else if (!right) velX = 0;
	if (right) velX = 2;
	else if (!left) velX = 0;
}

void Player::Collision(std::vector<Entity>& walls, std::vector<Entity>& coins, std::vector<Entity>& explosions) {
	for (Entity& w : walls) {
		if (IsColliding(pos.x + velX, pos.y, GetBounds(), w.GetBounds()))
			velX = 0;
		if (IsColliding(pos.x, pos.y + velY, GetBounds(), w.GetBounds()))
			velY = 0;
	}
	for (Entity& c : coins) {
		if (IsColliding(pos.x, pos.y, GetBounds(), c.GetBounds())) {
			coins.clear();
			score++;
		}
	}
	for (Entity& e : explosions) {
		if (IsColliding(pos.x, pos.y, GetBounds(), e.GetBlastBounds())) {
			if (healthCooldown > 100) {
				health--;
				healthCooldown = 0;
			}
		}
	}
	healthCooldown++;
}

void Player::SetHealth(int health) {
	this->health = health;
}
int Player::GetHealth() {
	return health;
}

void Player::SetScore(int score) {
	this->score = score;
}
int Player::GetScore() {
	return score;
}
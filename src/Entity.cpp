#include <SDL.h>
#include <SDL_image.h>

#include "../include/Entity.h"

Entity::Entity(Vector2f pos, SDL_Texture* texture, SDL_Rect rect)
	: velX(0), velY(0), pos(pos), texture(texture), rect(rect) {
}

bool Entity::IsColliding(int x, int y, SDL_Rect me, SDL_Rect other) {
	me.x = x;
	me.y = y;
	return me.x < other.x + other.w && me.x + me.w > other.x && me.y < other.y + other.h && me.y + me.h > other.y;
}

SDL_Rect Entity::GetBounds() {
	SDL_Rect rect = { pos.x, pos.y, 32, 32 };
	return rect;
}

SDL_Rect Entity::GetBlastBounds() {
	SDL_Rect rect = { pos.x - 48, pos.y - 48, 128, 128 };
	return rect;
}

void Entity::Tick() {

}

Vector2f& Entity::GetPos() {
	return pos;
}
SDL_Texture* Entity::GetTexture() {
	return texture;
}
SDL_Rect& Entity::GetRect() {
	return rect;
}
void Entity::SetVelX(int velX) {
	this->velX = velX;
}
void Entity::SetVelY(int velY) {
	this->velY = velY;
}
int Entity::GetVelX() {
	return velX;
}
int Entity::GetVelY() {
	return velY;
}
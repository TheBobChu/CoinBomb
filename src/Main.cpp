#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <random>
#include <string>

#include "../include/RenderWindow.h"
#include "../include/Entity.h"
#include "../include/Utils.h"
#include "../include/Player.h"
#include "../include/Bomb.h"

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "Failed: " << SDL_GetError() << std::endl;
	if (TTF_Init() < 0)
		std::cout << "TTF_init has failed. Error: " << SDL_GetError() << std::endl;
	return true;
}

bool SDLinit = init();

bool running = true;
std::vector<Entity> walls, coins, bombs, explosions;
SDL_Event event;
RenderWindow window("Game", 480, 320);

SDL_Texture* wallTexture = window.LoadTexture("res/gfx/wall.png");
SDL_Texture* boxTexture = window.LoadTexture("res/gfx/box.png");
SDL_Texture* coinTexture = window.LoadTexture("res/gfx/coin.png");
SDL_Texture* playerTexture = window.LoadTexture("res/gfx/player1.png");
SDL_Texture* bombTexture = window.LoadTexture("res/gfx/bomb.png");
SDL_Texture* explosionTexture = window.LoadTexture("res/gfx/bomb_explode2.png");
SDL_Texture* health = window.LoadTexture("res/gfx/health.png");

SDL_Rect health5crop = { 0, 23, 51, 9 };
SDL_Rect health4crop = { 0, 55, 51, 9 };
SDL_Rect health3crop = { 0, 87, 51, 9 };
SDL_Rect health2crop = { 0, 119, 51, 9 };
SDL_Rect health1crop = { 0, 151, 51, 9 };

Player player(Vector2f(200, 200), playerTexture, SDL_Rect{ 0, 0, 32, 32 });

SDL_Color white = { 255, 255, 255 };
TTF_Font* font32 = TTF_OpenFont("res/font/font.ttf", 32);

int fuse = 0, blast = 0, bombSpawn = 0;

std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<std::mt19937::result_type> distX(32, 416);
std::uniform_int_distribution<std::mt19937::result_type> distY(32, 256);
int coinRandX, coinRandY, bombRandX, bombRandY;

void SpawnCoins() {
	if (coins.size() == 0) {
		coinRandX = distX(rng);
		coinRandY = distY(rng);
		coins.emplace_back(Entity(Vector2f(coinRandX, coinRandY), coinTexture, SDL_Rect{ 0, 0, 32, 32 }));
	}
}

void SpawnBombs() {
	if (bombs.size() == 0) {
		bombRandX = distX(rng);
		bombRandY = distY(rng);
		bombs.emplace_back(Bomb(Vector2f(bombRandX, bombRandY), bombTexture, SDL_Rect{ 0, 0, 32, 32 }));
	}
}

void Tick() {
	player.Collision(walls, coins, explosions);
	player.Tick();
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			running = false;
		if(event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_w)
				player.up = true;
			if (event.key.keysym.sym == SDLK_s)
				player.down = true;
			if (event.key.keysym.sym == SDLK_a)
				player.left = true;
			if (event.key.keysym.sym == SDLK_d)
				player.right = true;
		}
		if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == SDLK_w)
				player.up = false;
			if (event.key.keysym.sym == SDLK_s)
				player.down = false;
			if (event.key.keysym.sym == SDLK_a)
				player.left = false;
			if (event.key.keysym.sym == SDLK_d)
				player.right = false;
		}
		break;
	}
	if (fuse > 75) {
		bombs.clear();
		explosions.emplace_back(Entity(Vector2f(bombRandX, bombRandY), explosionTexture, SDL_Rect{ 0, 0, 60, 55 }));
		fuse = 0;
	}
	fuse++;
	if (blast > 50) {
		explosions.clear();
		blast = 0;
	}
	if (explosions.size() > 0)
		blast++;
}

void Render() {
	window.Clear();
	for (Entity& w : walls)
		window.Render(w, 32, 32);
	for (Entity& c : coins)
		window.Render(c, 32, 32);
	for (Entity& b : bombs)
		window.Render(b, 32, 32);
	for (Entity& e : explosions)
		window.Render(e, 128, 128);
	window.Render(player, 32, 32);
	if (player.GetHealth() == 5)
		window.RenderHealth(health, health5crop);
	else if (player.GetHealth() == 4)
		window.RenderHealth(health, health4crop);
	else if (player.GetHealth() == 3)
		window.RenderHealth(health, health3crop);
	else if (player.GetHealth() == 2)
		window.RenderHealth(health, health2crop);
	else if (player.GetHealth() == 1)
		window.RenderHealth(health, health1crop);
	window.RenderText(160, 30, "Score:", font32, white);
	window.RenderText(235, 30, std::to_string(player.GetScore()).c_str(), font32, white);
	window.RenderText(330, 30, "Time:", font32, white);
	window.RenderText(395, 30, std::to_string((int)utils::HireTimeInSeconds()).c_str(), font32, white);
	window.Display();
}

void Run() {
	const float timeStep = 0.01f;
	float delta = 0.0f;
	float lastTime = utils::HireTimeInSeconds();
	while (running) {
		float now = utils::HireTimeInSeconds();
		delta += now - lastTime;
		lastTime = now;
		while (delta >= timeStep) {
			if (player.GetHealth() == 0)
				running = false;
			Tick();
			SpawnCoins();
			SpawnBombs();
			Render();
			delta -= timeStep;
		}
	}
}

void LoadLevel() {
	for (int i = 0; i < 320 / 32; i++) {
		if (i == 0 || i == 9) {
			for (int j = 0; j < 480 / 32; j++)
				walls.emplace_back(Entity(Vector2f(j * 32, i * 32), wallTexture, SDL_Rect{ 0, 0, 32, 32 }));
		}
		else {
			walls.emplace_back(Entity(Vector2f(0, i * 32), wallTexture, SDL_Rect{ 0, 0, 32, 32 }));
			walls.emplace_back(Entity(Vector2f(480 - 32, i * 32), wallTexture, SDL_Rect{ 0, 0, 32, 32 }));
		}
	}
}

int main(int argc, char* args[]) {
	LoadLevel();
	Run();
	window.CleanUp();
	TTF_CloseFont(font32);
	SDL_Quit();
	TTF_Quit();
	return 0;
}
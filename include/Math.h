#pragma once
#include <iostream>

struct Vector2f {
	int x, y;
	Vector2f() : x(0), y(0) {};
	Vector2f(int x, int y) : x(x), y(y) {};
	void Print() {
		std::cout << x << ", " << y << std::endl;
	}
};
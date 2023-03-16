#pragma once
#include <SDL.h>

namespace utils {
	inline float HireTimeInSeconds() {
		return SDL_GetTicks() * 0.001f;
	}
}
#pragma once
#include <SDL.h>
#include "BlockFall.h"
#include "Blocks.h"
class Game
{
public:
	Game();
	~Game();
	bool tick();
private:
	Game(const Game &);
	SDL_Window *window_;
	SDL_Renderer *renderer_;
	BlockFall BlockFall_;
	Blocks Blocks_;
	uint32_t moveTime_;
	void check(const Blocks &);
};
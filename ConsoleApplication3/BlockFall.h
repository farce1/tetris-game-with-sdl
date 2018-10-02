#pragma once
#include "Blocks.h"
#include <SDL.h>

class BlockFall
{
public:
	BlockFall();
	void draw(SDL_Renderer *);
	enum { Width = 10, Height = 20 };
	bool isCollision(const Blocks &t) const;
	void unite(const Blocks &);
	int score = 0;
private:
	bool data[Width][Height];
};
#include "BlockFall.h"
#include <iostream>

BlockFall::BlockFall() :
	data{ { false } }
{
}

void BlockFall::draw(SDL_Renderer *renderer) // Rysowanie klockow
{
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	for (auto x = 0; x < Width; ++x)
		for (auto y = 0; y < Height; ++y)
		{
			if (data[x][y])
			{
				SDL_Rect rect{ x * 720 / 2 / 10 + 1, y * 720 / 2 / 10 + 1, 720 / 2 / 10 - 2, 720 / 2 / 10 - 2 };
				SDL_RenderFillRect(renderer, &rect);
			}
			else
				SDL_RenderDrawPoint(renderer, x * 720 / 2 / 10 + 720 / 2 / 10 / 2,
					y * 720 / 2 / 10 + 720 / 2 / 10 / 2);
		}
}


bool BlockFall::isCollision(const Blocks &t) const  // Sprawdzenie kolizji
{
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (t.isBlock(x, y))
			{
				auto wx = t.x() + x;
				auto wy = t.y() + y;
				if (wx < 0 || wx >= Width || wy < 0 || wy >= Height)
					return true;
				if (data[wx][wy])
					return true;
			}
	return false;
}

void BlockFall::unite(const Blocks &t) // Ujednolicenie poziomu klockow
{
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (t.isBlock(x, y))
				data[t.x() + x][t.y() + y] = true;

	for (int y = Height - 1; y >= 0; --y)
	{
		bool solid = true;
		for (int x = 0; x < Width; ++x)
			if (!data[x][y])
			{
				solid = false;
				break;
			}
		if (solid)
		{
			for (int yy = y - 1; yy >= 0; --yy)
				for (int x = 0; x < Width; ++x)
					data[x][yy + 1] = data[x][yy];
			for (int x = 0; x < Width; ++x)
				data[x][0] = false;
			score += 1;
			std::cout << "P U N K T !!! " << "        "     << " ILOSC PKTOW : " << score << std::endl;
		}
	}
}


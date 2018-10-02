#include "Blocks.h"

Blocks::Blocks(Type type) :
	type_(type),
	x_(10 / 2 - 4 / 2),
	y_(0),
	angle_(0)
{}

void Blocks::draw(SDL_Renderer *renderer)
{
	switch (type_)
	{
	case I:
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
		break;
	case J:
		SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xff);
		break;
	case L:
		SDL_SetRenderDrawColor(renderer, 153, 102, 102, 0);
		break;
	case O:
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x7f, 0xff);
		break;
	case S:
		SDL_SetRenderDrawColor(renderer, 0xff, 0x7f, 0x00, 0xff);
		break;
	case T:
		SDL_SetRenderDrawColor(renderer, 0x7f, 0x40, 0x00, 0xff);
		break;
	case Z:
		SDL_SetRenderDrawColor(renderer, 0x00, 0x7f, 0x7f, 0xff);
		break;
	}

	for (auto x = 0; x < 4; ++x)
		for (auto y = 0; y < 4; ++y)
			if (isBlock(x, y))
			{
				SDL_Rect rect{ (x + x_) * 720 / 2 / 10, (y + y_) * 720 / 2 / 10, 720 / 2 / 10 - 1, 720 / 2 / 10 -1 };
				SDL_RenderFillRect(renderer, &rect);
			}
}

void Blocks::move(int dx, int dy)
{
	x_ += dx;
	y_ += dy;
}
void Blocks::rotate()
{
	angle_ += 3;
	angle_ %= 4;
}

bool Blocks::isBlock(int x, int y) const
{
	static const char *Shapes[][4] = {
		{
			" *  "
			" *  "
		" *  "
		" *  ",
		"    "
		"****"
		"    "
		"    ",
		" *  "
		" *  "
		" *  "
		" *  ",
		"    "
		"****"
		"    "
		"    ",
		},
		{
			"  * "
			"  * "
		" ** "
		"    ",
		"    "
		"*   "
		"*** "
		"    ",
		" ** "
		" *  "
		" *  "
		"    ",
		"    "
		"    "
		"*** "
		"  * ",
		},
		{
			" *  "
			" *  "
		" ** "
		"    ",
		"    "
		"*** "
		"*   "
		"    ",
		" ** "
		"  * "
		"  * "
		"    ",
		"  * "
		"*** "
		"    "
		"    ",
		},
		{
			"    "
			" ** "
		" ** "
		"    ",
		"    "
		" ** "
		" ** "
		"    ",
		"    "
		" ** "
		" ** "
		"    ",
		"    "
		" ** "
		" ** "
		"    ",
		},
		{
			"  * "
			" ** "
		" *  "
		"    ",
		"    "
		"**  "
		" ** "
		"    ",
		"  * "
		" ** "
		" *  "
		"    ",
		"    "
		"**  "
		" ** "
		"    ",
		},
		{
			" *  "
			" ** "
		" *  "
		"    ",
		"    "
		"*** "
		" *  "
		"    ",
		" *  "
		"**  "
		" *  "
		"    ",
		" *  "
		"*** "
		"    "
		"    ",
		},
		{
			" *  "
			" ** "
		"  * "
		"    ",
		"    "
		" ** "
		"**  "
		"    ",
		" *  "
		" ** "
		"  * "
		"    ",
		"    "
		" ** "
		"**  "
		"    ",
		},
	};
	return Shapes[type_][angle_][x + y * 4] == '*';
}
int Blocks::x() const
{
	return x_;
}
int Blocks::y() const
{
	return y_;
}
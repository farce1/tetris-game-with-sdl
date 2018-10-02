#include "Game.h"
#include <stdexcept>
#include <iostream>

Game::Game() : // Zaladowanie okna 
	Blocks_{ static_cast<Blocks::Type>(rand() % 7) },
	moveTime_(SDL_GetTicks())
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error("SDL_Init(SDL_INIT_VIDEO)");
	SDL_CreateWindowAndRenderer(720/2, 720, SDL_WINDOW_OPENGL, &window_, &renderer_);
	SDL_SetWindowPosition(window_,700, 126);
	SDL_SetWindowTitle(window_, "Moj piekny projekt TETRIS");

}

Game::~Game() // Destruktor
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

bool Game::tick() // Klawiaturka
{
	SDL_Event e;
	if (SDL_WaitEventTimeout(&e, 250))
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_DOWN:
			{
				Blocks t = Blocks_;
				t.move(0, 1);
				if (!BlockFall_.isCollision(t))
					Blocks_ = t;
			}
			break;
			case SDLK_RIGHT:
			{
				Blocks t = Blocks_;
				t.move(1, 0);
				if (!BlockFall_.isCollision(t))
					Blocks_ = t;
			}
			break;
			case SDLK_LEFT:
			{
				Blocks t = Blocks_;
				t.move(-1, 0);
				if (!BlockFall_.isCollision(t))
					Blocks_ = t;
			}
			break;
			case SDLK_SPACE:
			{
				Blocks t = Blocks_;
				t.rotate();
				if (!BlockFall_.isCollision(t))
					Blocks_ = t;
			}
			break;
			}
		}
		break;
		case SDL_QUIT:
			return false;
		}
	}
	SDL_SetRenderDrawColor(renderer_, 0, 0, 200, 255);
	SDL_RenderClear(renderer_);
	BlockFall_.draw(renderer_);
	Blocks_.draw(renderer_);
	if (SDL_GetTicks() > moveTime_) // Spadanie bloczkow
	{
		moveTime_ += 300;
		Blocks t = Blocks_;
		t.move(0, 1);
		check(t);
	}
	SDL_RenderPresent(renderer_);
	return true;
};

void Game::check(const Blocks &t) // Sprawdzanie logiki gry
{
	if (BlockFall_.isCollision(t))
	{
		BlockFall_.unite(Blocks_);
		Blocks_ = Blocks{ static_cast<Blocks::Type>(rand() % 7)};
		if (BlockFall_.isCollision(Blocks_))
		{
			BlockFall_ = BlockFall();
			SDL_Quit();
			std::cout << "Dziekuje, ze zagrales/as w moja gre!" << std::endl << "Made By Giorgio Sztuczini" << std::endl;
			
			
		}
	}
	else
	{
		Blocks_ = t;
	}

}
#pragma once
#include <SDL.h>
#include "hero.h"

class InputHandler
{
public:
	Hero* hero;
	Hero* hero2;


	InputHandler();
	~InputHandler();

	//abstract function
	virtual void update(SDL_Event* event) = 0;
};


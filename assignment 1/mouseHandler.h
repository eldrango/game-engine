#pragma once
#include "InputHandler.h"
class MouseHandler : public InputHandler
{
public:
	bool leftMousePressedDown = false;

	MouseHandler();
	~MouseHandler();

	void update(SDL_Event* event);
};

class mouseHandler
{
public:
	mouseHandler();
	~mouseHandler();
};

#include "KeyboardHandler.h"


KeyboardHandler::KeyboardHandler()
{
}


KeyboardHandler::~KeyboardHandler()
{
}

void KeyboardHandler::update(SDL_Event* event) {
	//button presses for our hero
	if (event->type == SDL_KEYDOWN) {
		//reset hero position if press R
		if (event->key.keysym.scancode == SDL_SCANCODE_R) {
			hero->pos.x = 200;
			hero->pos.y = 200;
		}
		//TODO add attacks or other actions here for button presses
	}

	//check if a button is held down
	//first get state of all keyboard buttons (1 pressed, 0 not pressed)
	const Uint8 *keystates = SDL_GetKeyboardState(NULL); //you can pass it a smaller array, or null to return all keys
			
     //player 1 movement
	if (event->key.keysym.scancode == SDL_SCANCODE_W) {
		if (hero->jump == true) {
			hero->velocity.y = -160;
			hero->jump = false;
		}
	}
	//down
	if (keystates[SDL_SCANCODE_S])
		hero->velocity.y = 80;
	//left
	if (keystates[SDL_SCANCODE_A])
		hero->velocity.x = -80;
	//right
	if (keystates[SDL_SCANCODE_D])
		hero->velocity.x = 80;
	if (keystates[SDL_SCANCODE_SPACE]) {
		hero->yOffset = 60;
		hero->punch = true;
	}
	//check if none are held down
	if (!keystates[SDL_SCANCODE_W] && !keystates[SDL_SCANCODE_S])
	{
		//then stop moving
		//hero->velocity.y = 0;
	}
	if (!keystates[SDL_SCANCODE_A] && !keystates[SDL_SCANCODE_D])
	{
		hero->velocity.x = 0;
	}

	//player 2 movement
	if (event->key.keysym.scancode == SDL_SCANCODE_UP)
		hero2->velocity.y = -160;
	//down
	if (keystates[SDL_SCANCODE_DOWN])
		hero2->velocity.y = 80;
	//left
	if (keystates[SDL_SCANCODE_LEFT])
		hero2->velocity.x = -80;
	//right
	if (keystates[SDL_SCANCODE_RIGHT])
		hero2->velocity.x = 80;
	//check if none are held down
	if (!keystates[SDL_SCANCODE_UP] && !keystates[SDL_SCANCODE_UP])
	{
		//then stop moving
		//hero2->velocity.y = 0;
	}
	if (!keystates[SDL_SCANCODE_LEFT] && !keystates[SDL_SCANCODE_RIGHT])
	{
		hero2->velocity.x = 0;
	}
}

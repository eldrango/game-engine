#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Animation.h"
#include "Entity.h"
#include "Hero.h"
#include <list>
#include "InputHandler.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include <SDL_ttf.h>
#include "vector.h"

//Git repo
//https://github.com/eldrango/game-engine.git

using namespace std;


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Animation* anim1;
Animation* anim2;
//texture pointer
SDL_Texture* texture;
SDL_Rect sourceRectangle;
SDL_Rect destinationRectangle;


int main(int argc, char **argv)
{
	//initiate SDL with the subsystems you want to use ie SDL_INIT_VIDEO
	//we're initaliasing all of them (sound, input, video etc)
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL Fail initialised!!!\n";
		return -1; //failed, dont continue rest of main code
	}
	else
	{
		cout << "SDL initialised success!!!\n";
	}

	//NEED TO INIT SDL_Image
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		cout << "sdl image did not load: " << IMG_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}

	//create window, params are: window title, window pos x, pos y, width, height, window flags
	window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN /*| SDL_WINDOW_FULLSCREEN*/);

	if (window != NULL) {
		cout << "Window created!" << endl;
	}
	else
	{
		cout << "Failed to create window!" << endl;
		return -1;
	}

	//create renderer to help draw stuff to the screen
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer != NULL)
	{
		cout << "Renderer created!" << endl;
	}
	else
	{
		cout << "Renderer FAILED!" << endl;
		return -1;
	}

	//INIT sdl ttf
	if (TTF_Init() != 0) {
		//if failed, complain about it
		cout << "SDL TTF failed!" << endl;
		SDL_Quit();
		return -1;
	}

	//gdb.txtet controller mapping
	SDL_GameControllerAddMappingsFromFile("assets/gamecontrollerdb.txt");

	//LOAD UP WHATEVER ASSETS HERE AFTER INIT

	//to load up an image, first load it up as a surface
	SDL_Surface* backgroundSurface = SDL_LoadBMP("assets/background.bmp");
	//then convert to texture
	SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
	//dont need surface anymore, free memory up
	SDL_FreeSurface(backgroundSurface);

	SDL_Rect BGDestination;
	BGDestination.x = 0;
	BGDestination.y = 0;

	//lets use pass by reference to work the width and height of our texture in pixels
	SDL_QueryTexture(backgroundTexture, NULL, NULL, &BGDestination.w, &BGDestination.h);
	cout << "texture size is : " << sourceRectangle.w << "x" << sourceRectangle.h << endl;

	sourceRectangle.x = 0;
	sourceRectangle.y = 0;
	sourceRectangle.w = 80;
	sourceRectangle.h = 50;
	destinationRectangle.x = 100;
	destinationRectangle.y = 50;
	destinationRectangle.w = sourceRectangle.w * 2; //copy the width of our texture
	destinationRectangle.h = sourceRectangle.h * 2; //copy the height of our texture


	//Play button  
	SDL_Surface* playSurface = IMG_Load("assets/play.png");
	SDL_Texture* play = SDL_CreateTextureFromSurface(renderer, playSurface);
	SDL_FreeSurface(playSurface);
	SDL_Rect playDest;
	playDest.x = 230;
	playDest.y = 50;
	//lets use pass by reference to work the width and height of our texture in pixels
	SDL_QueryTexture(play, NULL, NULL, &playDest.w, &playDest.h);
	cout << "texture size is : " << sourceRectangle.w << "x" << sourceRectangle.h << endl;

	//option button
	SDL_Surface* optionSurface = IMG_Load("assets/options.png");
	SDL_Texture* option = SDL_CreateTextureFromSurface(renderer, optionSurface);
	SDL_FreeSurface(optionSurface);
	SDL_Rect optionDest;
	optionDest.x = 226;
	optionDest.y = 155;
	//lets use pass by reference to work the width and height of our texture in pixels
	SDL_QueryTexture(option, NULL, NULL, &optionDest.w, &optionDest.h);

	//exit
	SDL_Surface* exitSurface = IMG_Load("assets/quit.png");
	SDL_Texture* exit = SDL_CreateTextureFromSurface(renderer, exitSurface);
	SDL_FreeSurface(exitSurface);
	SDL_Rect exitDest;
	exitDest.x = 247;
	exitDest.y = 252;
	//lets use pass by reference to work the width and height of our texture in pixels
	SDL_QueryTexture(exit, NULL, NULL, &exitDest.w, &exitDest.h);
	cout << "texture size is : " << sourceRectangle.w << "x" << sourceRectangle.h << endl;
													//setup time stuff
	Uint32 lastUpdate = SDL_GetTicks(); //set last update to current time (milliseconds to reach this bit of code)

	//Player 1
	list<Entity*> entities;
	SDL_Surface* toonSurface = IMG_Load("assets/toonSpriteSheet.png");

	//set colour of surface to be invisible
	SDL_SetColorKey(toonSurface, 1, SDL_MapRGB(toonSurface->format, 125, 2, 73));

	SDL_Texture* toon = SDL_CreateTextureFromSurface(renderer, toonSurface);
	SDL_FreeSurface;
	anim1 = new Animation(toon, renderer, 3, 0, 30, 28, 30, 0.2);
	Hero* hero = new Hero();
	hero->setAnimation(anim1);
	hero->setRenderer(renderer);

	Vector heroStartPos(10, 349);
	hero->setPosition(heroStartPos);

	entities.push_back(hero);


	//Player 2
	SDL_Surface* toonSurface2 = IMG_Load("assets/toonSpriteSheet.png");
	SDL_SetColorKey(toonSurface2, 1, SDL_MapRGB(toonSurface2->format, 125, 2, 73));
	SDL_Texture* toon2 = SDL_CreateTextureFromSurface(renderer, toonSurface2);
	SDL_FreeSurface;
	anim2 = new Animation(toon2, renderer, 3, 0, 30, 28, 30, 0.2);
	Hero* hero2 = new Hero();
	
	hero2->setAnimation(anim2);
	hero2->setRenderer(renderer);

	Vector hero2StartPos(592, 349);
	hero2->setPosition(hero2StartPos);

	entities.push_back(hero2);

	//CREATE INPUT HANDLERS
	KeyboardHandler keyboardHandler;
	keyboardHandler.hero = hero; //player 1
	keyboardHandler.hero2 = hero2;//player 2

	MouseHandler mouseHandler;
	SDL_Event e;

	SDL_RenderPresent(renderer);
	//game loop
	bool menuExit = true;
	while (menuExit) {
		//cant make background on sprite transparent
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		float DT = timeDiff / 1000.0;
		lastUpdate = SDL_GetTicks();
		SDL_RenderCopy(renderer, backgroundTexture, NULL, &BGDestination);
		SDL_RenderCopy(renderer, play, NULL, &playDest);
		SDL_RenderCopy(renderer, option, NULL, &optionDest);
		SDL_RenderCopy(renderer, exit, NULL, &exitDest);
		

		//toonSprite.x = toonSprite.w*int((SDL_GetTicks() / 100) % 5);
		
		//loop through and update and draw all entities
		for (list<Entity*>::iterator eIt = entities.begin(); eIt != entities.end(); eIt++) {
			(*eIt)->update(DT);
			(*eIt)->draw();
		}
		while (SDL_PollEvent(&e))
		{
			//check if user has clicked on the close window button
			if (e.type == SDL_QUIT) {
				//exit our loop,
				menuExit = false;
			}
			//check if user has 'pressed' a button(not held)
			if (e.type == SDL_KEYDOWN) {
				//see if ESC key was pressed
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					//exit loop
					menuExit = false;
				}
				
			}
			keyboardHandler.update(&e);
		}
		SDL_RenderPresent(renderer);

	}
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(play);
	SDL_DestroyTexture(option);
	SDL_DestroyTexture(exit);
	SDL_DestroyTexture(toon);
	SDL_DestroyTexture(toon2);
	//clean up renderer and window properly (aka clean up dynamic memory)
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//shut down subsystems and cleanup any setup it did earlier in sdl_init
	SDL_Quit();
	system("pause");
	return 0;
}
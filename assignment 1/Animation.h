#pragma once
#include <SDL.h>


class Animation
{
public:
	//basic information we need
	int numberOfFrames;
	int x, y;//positon of starting frame for sprite sheet
	int frameWidth, frameHeight;
	float frameDuration; //how long a frame stays on screen for
	SDL_Texture* spriteSheet; //reference to existing texture
	SDL_Renderer* renderer; //referencer to our renderer

	//current state of animation
	int currentFrame; //which frame to show
	float frameTimer; //how long has current frame been on screen for


	Animation(SDL_Texture* spriteSheet, SDL_Renderer* renderer, int numberOfFrames, int spriteX, int spriteY, int frameWidth, int frameHeight, float frameDuration);
	void update(float dt);
	void draw(int x, int y, int yOffset);
	void draw(int x, int y, float scale, int yOffset);
	void draw(int x, int y, bool flip, int yOffset);
};


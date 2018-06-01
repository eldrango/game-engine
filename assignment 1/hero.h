#pragma once
#include "Entity.h"
#include "Animation.h"
//#include "keyboardHandler.h"

class Hero :
	public Entity
{
private:
	Animation * animation = NULL;
	bool faceRight;
	
public:
	float gravity;
	int yOffset;
	bool jump;
	bool punch;

	Hero();
	~Hero();

	void setAnimation(Animation* animation);

	//overriding
	virtual void update(float dt);
	virtual void draw();
	void setJump();
	void setPunch();
};



#include "Hero.h"


Hero::Hero()
{
	gravity = 200;
}


Hero::~Hero()
{
}

void Hero::setAnimation(Animation* animation) {
	this->animation = animation;
}

//overriding
void Hero::update(float dt) {
	yOffset = 0;
	//face direction based on velocity.x value
	if (velocity.x > 0) {
		faceRight = false;
	}
	if (velocity.x < 0) {
		faceRight = true;
	}
	//gravity
	if (pos.y < 346) {
		velocity.y += gravity * dt;
	}

	//ground
	if (pos.y > 346) {
		//force us back on screen
		pos.y = 346;
		velocity.y = 0;
	}
	//use basic entity movement to move around
	updateMovement(dt);

	//update animations too
	animation->update(dt);
}
void Hero::draw() {
	if (animation != NULL) {
		if (punch == false) {
			if (velocity.y > 0 || velocity.y < 0) {
				yOffset = 90;
			}
			else if (velocity.x < 0 || velocity.x > 0) {
				yOffset = 30;
			}
		}
		else
			yOffset = 60;
		if (faceRight == false) {
			animation->draw(pos.x, pos.y, yOffset);

		}
		else {
			animation->draw(pos.x, pos.y, this->faceRight, yOffset);
		}
	}
}

void Hero::setJump() {
	jump = true;
}

void Hero::setPunch() {
	punch = false;
}



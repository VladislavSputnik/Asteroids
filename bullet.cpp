#include "bullet.h"

namespace Tmpl8 
{
	bullet::bullet() :
		movementSpeed(BULLET_SPEED),
		rotation(0),
		velocity({ 0, 0 }),
		canDelete(false),
		position({ 0, 0 })
	{
	}

	void bullet::Init() {
		startTime = SDL_GetTicks();
	}

	void bullet::Update() {

		if (startTime + LIFE_TIME < SDL_GetTicks())
			canDelete = true;

		// Warp around X axis
		if (position.x < 0)
			position.x = SCRWIDTH;
		if (position.x > SCRWIDTH)
			position.x = 0;

		// Warp around Y axis
		if (position.y < 0)
			position.y = SCRHEIGHT;
		if (position.y > SCRHEIGHT)
			position.y = 0;

		// Move forward
		position += velocity;

		// Render bullet
		screen->Box(position.x, position.y, (position.x + BULLET_SIZE), (position.y + BULLET_SIZE), 0xFFFFFF);
		//screen->Plot(position.x, position.y, 0xffffff);
	}

};

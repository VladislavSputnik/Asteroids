#include "player.h"

namespace Tmpl8
{

player::player() :
	movementSpeed(0.006f),
	rotationSpeed(0.3f),
	drag(0.99f),
	velocity({ 0,0 }),
	position({ 0,0 }),
	rotation(0),
	scale({ -4.f, -4.f }),
	colliderScale({-5.f,-5.f}),
	health(START_HEALTH),
	isBoosting(false),

	polygonSize(sizeof(polygon) / sizeof(polygon[0])),
	polygon{
		{ 3,-2 },
		{ -3, 0 },
		{ 3,2 },
		{ 2.4f,1.8f },
		{ 2.4f,-1.8f }
		},

	polygonFlameSize(sizeof(polygonFlame) / sizeof(polygonFlame[0])),
	polygonFlame{
		{2.6f,-1.f},
		{2.6f,1.f},
		{4.f,0.f}
		},

	colliderPolygonSize(3),
	colliderPolygon{
		{3.f,-2.f},
		{-3.f,0.f},
		{3.f,2.f}
		}
{
}

void player::Update(float deltaTime)
{
	delta = deltaTime;
	currentTime = SDL_GetTicks();

	// Set rotation value turn over
	if (rotation > 360)
		rotation = 0;
	else if (rotation < 0)
		rotation = 360;

	
	// Warp around X axis
	if (position.x < 0)
		position.x = SCRWIDTH;
	else if (position.x > SCRWIDTH)
		position.x = 0;

	// Warp around Y axis
	if (position.y < 0)
		position.y = SCRHEIGHT;
	else if (position.y > SCRHEIGHT)
		position.y = 0;

	// Floaty X
	if (velocity.x != 0)
		velocity.x *= drag;

	// Floaty Y
	if (velocity.y != 0)
		velocity.y *= drag;

	// Set player position based on velocity
	position += velocity;

	//Set render screen
	render.SetTarget(screen);

	// Draw polygons
	render.Draw(polygon, polygonSize, position.x, position.y, rotation, scale);
	if (isBoosting)
		render.Draw(polygonFlame, polygonFlameSize, position.x, position.y, rotation, scale);
}

void player::Input(bool _isTurningRight, bool _isTurningLeft, bool _isBoosting, bool _isShooting, bool _isWarping) {
	
	// Rotate right (RIGHT ARROW)
	if (_isTurningRight)
		Rotate(rotationSpeed * delta);

	// Rotate left (LEFT ARROW)
	if (_isTurningLeft)
		Rotate(-rotationSpeed * delta);

	// Move forward (UP ARROW)
	if (_isBoosting)
	{
		isBoosting = true;
		Move();
	}
	else
		isBoosting = false;

	// Shooting (SPACE)
	if (_isShooting && (currentTime - lastTimeShooting) > BULLET_INTERVAL)
	{
		lastTimeShooting = SDL_GetTicks();
		shoot = true;
	}
	else
		shoot = false;
	
	// Hyperspace (Return)
	if (_isWarping && (currentTime - lastTimeHyperspacing) > HYPERSPACE_INVERVAL)
	{
		lastTimeHyperspacing = SDL_GetTicks();
		Hyperspace();
	}
	
}

void player::Move()
{
	vec2 direction;
	direction.x = (movementSpeed * delta) * cos(math::DegToRad(rotation));
	direction.y = (movementSpeed * delta) * sin(math::DegToRad(rotation));
	velocity += direction;
}

void player::Hyperspace()
{
	position = { (rand() % SCRWIDTH + 1.f),(rand() % SCRHEIGHT + 1.f) };
	velocity = { 0, 0 };
}

void player::Respawn() 
{
	position = { SCRWIDTH / 2, SCRHEIGHT / 2 };
	velocity = { 0, 0 };
	rotation = 270;
}

void player::Reset() {
	position = { SCRWIDTH / 2, SCRHEIGHT / 2 };
	velocity = { 0, 0 };
	rotation = 270;
	health = START_HEALTH;
}

};

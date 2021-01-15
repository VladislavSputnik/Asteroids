#include "asteroid.h"
#include "math.h"

namespace Tmpl8
{
asteroid::asteroid() :
	movementSpeed(0.9f),
	rotation(0),
	velocity({ 0,0 }),
	size(3),
	radius(0),
	position({ 0,0 }),
	scale{ 20, 20 }
{
}

void asteroid::Init() {
	vec2 direction;
	rotation = rand() % 361;
	direction.x = movementSpeed * cos(math::DegToRad(rotation));
	direction.y = movementSpeed * sin(math::DegToRad(rotation));
	velocity += direction;
}

void asteroid::Update() {

	// Set asteroid size
	switch (size) {
	case 1:
		scale.Set(SMALL_SIZE);
		break;
	case 2:
		scale.Set(MEDIUM_SIZE);
		break;
	case 3:
		scale.Set(LARGE_SIZE);
		break;
	default:
		scale.Set(SMALL_SIZE);
		break;
	}

	// Set radius
	radius = 2 * scale.x;

	//Position Update
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

	// Set player position based on velocity
	position += velocity;

	// Set screen to render on
	render.SetTarget(screen);

	// Draw polygon
	render.Draw(shape, shapeLength, position.x, position.y, scale);
}

bool asteroid::Collision(const bullet& _bullet) {
	if (math::Dist(position, _bullet.position) <= radius * radius)
		return true;
	return false;
}
bool asteroid::Collision(const player& _player) {
	if (math::Dist(_player.colliderPolygon[0] + _player.position,position) <= radius * radius)
		return true;
	if (math::Dist(_player.colliderPolygon[1] + _player.position, position) <= radius * radius)
		return true;
	if (math::Dist(_player.colliderPolygon[2] + _player.position, position) <= radius * radius)
		return true;

	return false;
}

};
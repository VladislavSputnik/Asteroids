#pragma once
#include "render.h"
#include "math.h"

#define START_HEALTH 3
#define MAX_HEALTH 5

#define HYPERSPACE_INVERVAL 10000					// Miliseconds interval between hyperspaces
#define BULLET_INTERVAL 200							// Miliseconds interval between shots

namespace Tmpl8 {

class player
{
private:

	// Movement
	float movementSpeed;
	float rotationSpeed;
	float drag;
	vec2 velocity;

	// Surface
	Surface* screen;
	render render;

	// Delta time
	int delta;
	int currentTime;
	int lastTimeShooting;							// Last time when bullet being shot
	int lastTimeHyperspacing;						// Last the when the user did a hyperspace

public:

	// Transform
	vec2 position;
	float rotation;
	vec2 scale;
	vec2 colliderScale;

	// Data
	int health;
	bool isBoosting;
	bool shoot;

	// Shape
	vec2 polygon[5];
	int polygonSize;
	vec2 polygonFlame[3];
	int polygonFlameSize;
	vec2 colliderPolygon[3];
	int colliderPolygonSize;

	// Functions
	player();
	void Update(float deltaTime);
	void Input(bool _isTurningRight, bool _isTurningLeft, bool _isBoosting, bool _isShooting, bool _isWarping);
	void Move();
	void Hyperspace();
	void Respawn();
	void Rotate(float _add) { rotation += _add; }
	void Reset();

	// Set
	void SetTarget(Surface* surface) { screen = surface; }
	void SetLastTimeShooting(unsigned int _value) { lastTimeShooting = _value; }

	// Get
	float GetMovementSpeed() { return movementSpeed; }
	float GetRotationSpeed() { return rotationSpeed; }
	float GetDrag() { return drag; }
	vec2 GetVelocity() { return velocity; }
};

};
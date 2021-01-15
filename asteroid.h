#pragma once
#include "precomp.h"
#include "math.h"
#include "render.h"
#include "bullet.h"
#include "player.h"

#define LARGE_SIZE 15
#define MEDIUM_SIZE 10
#define SMALL_SIZE 5

namespace Tmpl8 {

class asteroid
{
private:

	// Movement
	float movementSpeed;
	float rotation;
	vec2 velocity;

	// Data
	int size;
	// 1 = small
	// 2 = medium
	// 3 = large

	// Surface
	Surface* screen;
	render render;

public:

	// Transform
	vec2 position;
	vec2 scale;

	// Data
	float radius;
	bool debug;

	//shape
	vec2* shape;
	int shapeLength;

	// Functions
	asteroid();
	void Init();
	void Update();
	bool Collision(const bullet& _bullet);
	bool Collision(const player& _player);

	// Set
	void SetTarget(Surface* _surface) { screen = _surface; }
	void SetShape(vec2* _vec2, int _length) { shape = _vec2; shapeLength = _length; }
	void SetSize(int _size) { size = _size; }
	void SetMovementSpeed(float _speed) { movementSpeed = _speed; }

	// Get
	float GetMovementSpeed() { return movementSpeed; }
	float GetRotation() { return rotation; }
	vec2 GetVelocity() { return velocity; }
	int GetSize() { return size; }
	float GetRadius() { return radius; }

};

};
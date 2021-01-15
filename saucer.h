#pragma once
#include "bullet.h"
#include "render.h"
#include "player.h"

#define MIN_MOVE_TIME 1000
#define MAX_MOVE_TIME 3000

#define BULLET_INTERVAL 1000
#define MAX_SAUCER_BULLETS 4

#define SMALL_SCALE 5
#define LARGE_SCALE 10

static enum SaucerSize {
	SMALL_SAUCER = 0,
	LARGE_SAUCER = 1
};

namespace Tmpl8 {

	class saucer
	{
	private:

		// Polygon shape
		vec2 saucerPolygon[12];
		int saucerPolygonLength;

		// Transform
		vec2 position;
		float rotation;
		float bulletRotation;
		vec2 scale;

		// Movement
		vec2 velocity;
		float movementSpeed;

		// Collision
		float colliderRadius;

		// Bullets
		bullet saucerBullets[MAX_SAUCER_BULLETS];
		int saucerBulletSize;

		// Surface
		Surface* screen;
		render render;

		// Data
		int size;
		int currentTime;
		int lastTime;
		int lastTimeShot;
		int moveTime;
		bool canShoot;

	public:

		bool isPaused;

		// Functions
		saucer();
		void Update(float _deltaTime, player& _player);
		void RotationOverflow();
		void ScreenWrapAround();
		void SetRandomDest();
		void ChangeSize(unsigned int _size);

		bool Collision(player& _player);

		// saucer bullet handling
		void CreateSaucerBullet();
		void RemoveSaucerBullet(unsigned int _index);

		// Get
		vec2 GetPosition() { return position; }
		float GetColliderRadius() {	return colliderRadius * scale.x; }
		int GetSize() { return size; }

		// Set
		void SetPosition(vec2 _position) { position = _position; }
		void SetScale(vec2 _scale) { scale = _scale; }
		void SetTarget(Surface* _surface) { screen = _surface; }
		void SetPause(bool _value) { isPaused = _value; }
	};

};
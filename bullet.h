#pragma once
#include "precomp.h"
#include "math.h"

#define BULLET_SIZE 1
#define LIFE_TIME 1500 // miliseconds
#define BULLET_SPEED 2.8f 

namespace Tmpl8 {

	class bullet
	{
	private:

		// Movement
		float movementSpeed;
		float rotation;
		vec2 velocity;

		// Surface
		Surface* screen;

		// Data
		int startTime;
		bool canDelete;

	public:

		// Transform
		vec2 position;

		// Functions
		bullet();
		void Init();
		void Update();

		// Set
		void SetTarget(Surface* _surface) { screen = _surface; }
		void SetRotation(float _rotation) { rotation = _rotation; }
		void SetVelocity(vec2 _vec2) { velocity = _vec2; }

		// Get
		float GetMovementSpeed() { return movementSpeed; }
		float GetRotation() { return rotation;  }
		vec2 GetVelocity() { return velocity; }
		bool GetDeleteState() { return canDelete; }
	};

}


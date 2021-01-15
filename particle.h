#pragma once

#define PARTICLE_AMOUNT 10
#define PARTICLE_SPEED 2.5f
#define PARTICLE_STEPS 10
#define PARTICLE_INTERVAL 50

namespace Tmpl8 
{
	class particle
	{
	public:
		particle();
		void Update();
		void Draw();
		void SetTarget(Surface* _surface) { screen = _surface; }
		void SetPosition(const vec2& _position) { position = _position; }
		bool GetDeleteState() { return canDelete; }

	private:
		Surface* screen;

		vec2 position;
		vec2 particlePosition[PARTICLE_AMOUNT];
		float directions[PARTICLE_AMOUNT];
		float speed[PARTICLE_AMOUNT];

		int steps;
		int currentTime;
		int lastTime;

		bool canDelete;
	};
};
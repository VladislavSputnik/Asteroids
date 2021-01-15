#include "precomp.h"
#include "particle.h"
#include "math.h"

namespace Tmpl8
{
	particle::particle()
	{
		position = { 0, 0 };
		steps = 0;
		currentTime = 0;
		lastTime = 0;
		canDelete = false;

		for (int i = 0; i < PARTICLE_AMOUNT; i++) {
			directions[i] = rand() % 361;
			speed[i] = (rand() % 20);
		}
	}

	void particle::Update() {

		currentTime = SDL_GetTicks();
		if ((currentTime - lastTime) > PARTICLE_INTERVAL) {
			lastTime = SDL_GetTicks();

			for (int i = 0; i < PARTICLE_AMOUNT; i++) {
				particlePosition[i] = position;
				particlePosition[i].x += speed[i] * sin(math::DegToRad(directions[i]));
				particlePosition[i].y += speed[i] * cos(math::DegToRad(directions[i]));

				speed[i] += PARTICLE_SPEED;
			}

			if (steps > PARTICLE_STEPS)
				canDelete = true;
			steps++;
		}

		Draw();
	}

	void particle::Draw() {
		for (int i = 0; i < PARTICLE_AMOUNT; i++) {
			screen->Plot(particlePosition[i].x, particlePosition[i].y, 0xFFFFFF);
		}
	}
};
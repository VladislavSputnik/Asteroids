#pragma once
#include "precomp.h"
#include "player.h"
#include "asteroid.h"
#include "bullet.h"
#include "particle.h"
#include "saucer.h"

#define MAX_ASTEROID_AMOUNT 44						// Max	amount of asteroids that can be on screen
#define ASTEROID_SPLIT_AMOUNT 2						// In how many pieces the asteroids breaks when destroyed
#define MAX_BULLET_AMOUNT 4							// Max amount of bullet that can be on screen
#define MAX_PARTICLE_AMOUNT 22						// Max amount of particle objects on screen

// Score values
#define SCORE_SMALL_ASTEROID 100
#define SCORE_MEDIUM_ASTEROID 50
#define SCORE_LARGE_ASTEROID 20
#define SCORE_SMALL_SAUCER 1000
#define SCORE_LARGE_SAUCER 200

namespace Tmpl8
{
	class entitymanager
	{
	public:
		entitymanager();

		void SetTarget(Surface* _surface) { screen = _surface; }
		void Update();
		void Collision(player& _player, saucer _saucer);
		void DestroyAll();

		// Asteroid handling
		void CreateAsteroid(const vec2& _position, int _size, int _amount);
		void RemoveAsteroid(unsigned int _index);

		// Bullet handling
		void CreateBullet(player& _player);
		void RemoveBullet(unsigned int _index);

		// Particle handling
		void CreateParticle(const vec2& _position);
		void RemoveParticle(unsigned int _index);

		int GetAsteroidSize() { return asteroidSize; }

		void SetScore(unsigned int _score) { score = _score; }

		// Game logic data
		int score;
		bool asteroidPlayerCollision;

	private:
		Surface* screen;

		// Asteroid data
		asteroid asteroids[MAX_ASTEROID_AMOUNT];		// Asteroid object array
		int asteroidSize;								// Amount off asteroids in array used

		// Bullet data
		bullet bullets[MAX_BULLET_AMOUNT];				// Bullet object array
		int bulletSize;									// Amount off bullets in array used

		// Particle data
		particle particles[MAX_PARTICLE_AMOUNT];		// Particle object array
		int particleSize;								// Amount of particles in array used
	};
};


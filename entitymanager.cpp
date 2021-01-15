#include "entitymanager.h"
#include "shapes.h"

namespace Tmpl8 
{
	entitymanager::entitymanager() 
	{
		asteroidSize = 0;
		bulletSize = 0;
		particleSize = 0;
		score = 0;
		asteroidPlayerCollision = false;
	}

	void entitymanager::Update() 
	{
		// Update Asteroids
		for (int i = 0; i < asteroidSize; i++)
		{
			asteroid& a = asteroids[i];
			a.Update();
		}

		// Update bullets
		for (int i = 0; i < bulletSize; i++)
		{
			bullet& b = bullets[i];
			b.Update();
			if (b.GetDeleteState())
				RemoveBullet(i);
		}

		// Update particles
		for (int i = 0; i < particleSize; i++)
		{
			particle& p = particles[i];
			p.Update();
			if (p.GetDeleteState())
				RemoveParticle(i);
		}
	}

	void entitymanager::DestroyAll()
	{
		asteroidSize = 0;
		bulletSize = 0;
		particleSize = 0;
	}

	void entitymanager::Collision(player& _player, saucer _saucer) 
	{
		// Detect collision
		for (int i = 0; i < asteroidSize; i++)
		{
			asteroid& a = asteroids[i];

			// Detect collision asteroid -> player
			if (a.Collision(_player) && !asteroidPlayerCollision)
				asteroidPlayerCollision = true;

			if (math::Dist(_saucer.GetPosition(), a.position) <= _saucer.GetColliderRadius() * _saucer.GetColliderRadius()+ a.radius* a.radius) {
				CreateParticle(a.position);
				_saucer.isPaused = true;
				switch (a.GetSize())
				{
				case 1:
					score += SCORE_SMALL_ASTEROID;
					break;
				case 2:
					score += SCORE_MEDIUM_ASTEROID;
					break;
				case 3:
					score += SCORE_LARGE_ASTEROID;
					break;
				default:
					break;
				}
				if (a.GetSize() != 1) {
					CreateAsteroid(a.position, (a.GetSize() - 1), 2);
				}
				RemoveAsteroid(i);
			}

			// Detect collision asteroid -> bullet
			for (int j = 0; j < bulletSize; j++)
			{
				bullet& b = bullets[j];


				if (math::Dist(_saucer.GetPosition(), b.position) <= _saucer.GetColliderRadius() * _saucer.GetColliderRadius())
				{
					switch (_saucer.GetSize())
					{
					case SMALL_SAUCER:
						score += SCORE_SMALL_SAUCER;
						break;
					case LARGE_SAUCER:
						score += SCORE_LARGE_SAUCER;
						break;
					default:
						break;
					}
					_saucer.isPaused = true;
				}

				if (a.Collision(b))
				{
					switch (a.GetSize())
					{
					case 1:
						score += SCORE_SMALL_ASTEROID;
						break;
					case 2:
						score += SCORE_MEDIUM_ASTEROID;
						break;
					case 3:
						score += SCORE_LARGE_ASTEROID;
						break;
					default:
						break;
					}
					CreateParticle(a.position);
					RemoveBullet(j);
					if (a.GetSize() != 1) {
						CreateAsteroid(a.position, (a.GetSize() - 1), 2);
					}
					RemoveAsteroid(i);
				}
			}

		}
	}

	// Asteroid handling
	void entitymanager::CreateAsteroid(const vec2& _position, int _size, int _amount) 
	{
		for (int i = 0; i < _amount; i++)
		{
			if (asteroidSize < MAX_ASTEROID_AMOUNT)
			{
				asteroid tmpObj;
				tmpObj.SetTarget(screen);

				// Increase speed
				tmpObj.SetMovementSpeed(tmpObj.GetMovementSpeed() + ((rand() % 10) / 10.f));

				tmpObj.Init();
				tmpObj.position = _position;
				tmpObj.SetSize(_size);

				// Get random shape
				switch (rand() % 4)
				{
				case 0:
					tmpObj.SetShape(asteroidPolygon_01, asteroidPolygonLength[0]);
					break;
				case 1:
					tmpObj.SetShape(asteroidPolygon_02, asteroidPolygonLength[1]);
					break;
				case 2:
					tmpObj.SetShape(asteroidPolygon_03, asteroidPolygonLength[2]);
					break;
				case 3:
					tmpObj.SetShape(asteroidPolygon_04, asteroidPolygonLength[3]);
					break;
				default:
					tmpObj.SetShape(asteroidPolygon_01, asteroidPolygonLength[0]);
					break;
				}

				asteroids[asteroidSize] = tmpObj;
				asteroidSize++;
			}
		}
	}
	void entitymanager::RemoveAsteroid(unsigned int _index) 
	{
		int count = 0;

		// Copy array to temp array
		asteroid tmpArray[MAX_ASTEROID_AMOUNT];
		for (int i = 0; i < MAX_ASTEROID_AMOUNT; i++)
		{
			tmpArray[i] = asteroids[i];
		}

		// Copy back to original array without one indexed object
		for (int i = 0; i < MAX_ASTEROID_AMOUNT; i++)
		{
			if (i != _index)
			{
				asteroids[count] = tmpArray[i];
				count++;
			}
		}
		asteroidSize--;
	}

	// Bullet handling
	void entitymanager::CreateBullet(player& _player)
	{
		if (bulletSize < MAX_BULLET_AMOUNT)
		{
			bullet tmpObj;

			tmpObj.SetTarget(screen);

			vec2 velocity = _player.GetVelocity();
			velocity.x += tmpObj.GetMovementSpeed() * cos(math::DegToRad(_player.rotation));
			velocity.y += tmpObj.GetMovementSpeed() * sin(math::DegToRad(_player.rotation));

			tmpObj.SetVelocity(velocity);
			tmpObj.position = _player.position;

			tmpObj.Init();
			tmpObj.Update();

			bullets[bulletSize] = tmpObj;
			bulletSize++;
		}
	}
	void entitymanager::RemoveBullet(unsigned int _index)
	{
		int count = 0;

		// Copy array to temp array
		bullet tmpArray[MAX_BULLET_AMOUNT];
		for (int i = 0; i < MAX_BULLET_AMOUNT; i++)
		{
			tmpArray[i] = bullets[i];
		}

		// Copy back to original array without one indexed object
		for (int i = 0; i < MAX_BULLET_AMOUNT; i++)
		{
			if (i != _index)
			{
				bullets[count] = tmpArray[i];
				count++;
			}
		}

		bulletSize--;
	}

	// Particle handling
	void entitymanager::CreateParticle(const vec2& _position)
	{
		if (particleSize < MAX_PARTICLE_AMOUNT)
		{
			particle tmpObj;
			tmpObj.SetTarget(screen);
			tmpObj.SetPosition(_position);
			particles[particleSize] = tmpObj;
			particleSize++;
		}
	}
	void entitymanager::RemoveParticle(unsigned int _index)
	{
		int count = 0;

		// Copy array to temp array
		particle tmpArray[MAX_PARTICLE_AMOUNT];
		for (int i = 0; i < MAX_PARTICLE_AMOUNT; i++)
		{
			tmpArray[i] = particles[i];
		}

		// Copy back to original array without one indexed object
		for (int i = 0; i < MAX_PARTICLE_AMOUNT; i++)
		{
			if (i != _index)
			{
				particles[count] = tmpArray[i];
				count++;
			}
		}

		particleSize--;
	}
};

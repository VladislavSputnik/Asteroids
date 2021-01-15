#include "precomp.h"
#include "saucer.h"

namespace Tmpl8 
{
	saucer::saucer() :
		position({ 0, 0 }),
		rotation(0),
		scale({ -10.f, -10.f }),
		velocity({ 0, 0 }),
		movementSpeed(0.1f),
		colliderRadius(2.f),
		size(0),
		currentTime(0),
		lastTime(0),
		lastTimeShot(0),
		moveTime(rand() % (MAX_MOVE_TIME - MIN_MOVE_TIME) + MIN_MOVE_TIME),
		canShoot(false),
		isPaused(true),

		saucerPolygonLength(sizeof(saucerPolygon) / sizeof(saucerPolygon[0])),
		saucerPolygon {
			{-1.f,-0.8f},
			{-2.f,0.f},
			{-1.f,0.8f},
			{-0.6f,1.6f},
			{0.6f,1.6f},
			{1.f,0.8f},
			{-1.f,0.8f},
			{1.f,0.8f},
			{2.f,0.f},
			{-2.f,0.f},
			{2.f,0.f},
			{1.f,-0.8f}
		}
	{
	}

	void saucer::Update(float _deltaTime, player& _player) 
	{
		if (!isPaused) 
		{
			currentTime = SDL_GetTicks();

			RotationOverflow();
			ScreenWrapAround();

			// Set new Dest after (1000 to 3000) milliseconds
			if ((currentTime - lastTime) > moveTime)
			{
				SetRandomDest();
				moveTime = rand() % (MAX_MOVE_TIME - MIN_MOVE_TIME) + MIN_MOVE_TIME;
				lastTime = currentTime;
			}

			// Update saucer bullets
			for (int i = 0; i < saucerBulletSize; i++)
			{
				saucerBullets[i].Update();
				if (saucerBullets[i].GetDeleteState())
					RemoveSaucerBullet(i);
			}

			// Shoot every interval
			if ((currentTime - lastTimeShot) > BULLET_INTERVAL)
			{
				if (size == SMALL_SAUCER)
					bulletRotation = atan2(_player.position.y - position.y, _player.position.x - position.x) * 180 / PI;
				else
					bulletRotation = rand() % 361;

				CreateSaucerBullet();
				lastTimeShot = currentTime;
			}

			// Move saucer
			position += velocity * _deltaTime;

			//Set render screen
			render.SetTarget(screen);

			// Draw saucer
			render.Draw(saucerPolygon, saucerPolygonLength, position.x, position.y, 0, scale);
		}
	}

	void saucer::RotationOverflow() 
	{
		// Set rotation value turn over
		if (rotation > 360)
			rotation = 0;
		else if (rotation < 0)
			rotation = 360;
	}

	void saucer::ScreenWrapAround() 
	{
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
	}

	void saucer::SetRandomDest() 
	{
		// Get random dir (0 to 7) * 45 degrees
		rotation = (rand() % 8) * 45;

		// Set Velocity
		velocity.x = movementSpeed * cos(math::DegToRad(rotation));
		velocity.y = movementSpeed * sin(math::DegToRad(rotation));
	}

	void saucer::ChangeSize(unsigned int _size) 
	{
		size = _size;
		
		if (size == SMALL_SAUCER)
			scale = { -SMALL_SCALE,-SMALL_SCALE };
		else if(size == LARGE_SAUCER)
			scale = { -LARGE_SCALE,-LARGE_SCALE };
	}

	// Collision
	bool saucer::Collision(player& _player)
	{
		// saucer player collision


		// Bullet player collision
		vec2 pos1 = _player.colliderPolygon[0] + _player.position;
		vec2 pos2 = _player.colliderPolygon[1] + _player.position;
		vec2 pos3 = _player.colliderPolygon[2] + _player.position;
		float areaPlayerCollider = abs((pos2.x-pos1.x)*(pos3.y-pos1.y)-(pos3.x-pos1.x)*(pos2.y-pos1.y));
		
		for (int i = 0; i < saucerBulletSize; i++) 
		{
			vec2 p = saucerBullets[i].position;
			float area1 = abs((pos1.x - p.x) * (pos2.y - p.y) - (pos2.x - p.x) * (pos1.y - p.y));
			float area2 = abs((pos2.x - p.x) * (pos3.y - p.y) - (pos3.x - p.x) * (pos2.y - p.y));
			float area3 = abs((pos3.x - p.x) * (pos1.y - p.y) - (pos1.x - p.x) * (pos3.y - p.y));

			if (area1 + area2 + area3 <= areaPlayerCollider)
				return true;
		}
		return false;
	}

	// Saucer bullet handling
	void saucer::CreateSaucerBullet()
	{
		if (saucerBulletSize < MAX_SAUCER_BULLETS)
		{
			bullet tmpObj;
			tmpObj.SetTarget(screen);

			vec2 bulletVelocity;
			bulletVelocity.x = tmpObj.GetMovementSpeed() * cos(math::DegToRad(bulletRotation));
			bulletVelocity.y = tmpObj.GetMovementSpeed() * sin(math::DegToRad(bulletRotation));

			tmpObj.SetVelocity(bulletVelocity);
			tmpObj.position = position;

			tmpObj.Init();
			tmpObj.Update();

			saucerBullets[saucerBulletSize] = tmpObj;
			saucerBulletSize++;
		}
	}
	void saucer::RemoveSaucerBullet(unsigned int _index)
	{
		int count = 0;

		// Copy array to temp array
		bullet tmpArray[MAX_SAUCER_BULLETS];
		for (int i = 0; i < MAX_SAUCER_BULLETS; i++)
		{
			tmpArray[i] = saucerBullets[i];
		}

		// Copy back to original array without one indexed object
		for (int i = 0; i < MAX_SAUCER_BULLETS; i++)
		{
			if (i != _index)
			{
				saucerBullets[count] = tmpArray[i];
				count++;
			}
		}

		saucerBulletSize--;
	}
};
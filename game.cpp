#include "precomp.h" // include this first in every .cpp file
#include "game.h"
#include "render.h"
#include <ctime>

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		// Set targets
		render.SetTarget(screen);
		spaceShip.SetTarget(screen);
		enemy.SetTarget(screen);
		
		// Initialize object values
		entityManager.SetTarget(screen);
		enemy.ChangeSize(1);
		enemy.SetPause(false);

		// Initialize game values
		gameState = 0;
		timeOnRespawn = 0;
		currentTime = 0;
		highscoresSize = 0;
		wave = 0;
		prevScore = 0;
		isRespawning = false;

		// Initialize text values
		textScale.Set(TEXT_SCALE, -TEXT_SCALE);
		scoreScale.Set(SCORE_SCALE, -SCORE_SCALE);
		highscoreScale.Set(HIGHSCORE_SCALE, -HIGHSCORE_SCALE);
		vec2 textPos = { 0,0 };

		// Initialize debug values
		debugToggle = false;
		isDown = false;

		// Initialize frame data values
		startTime = 0;
		endTime = 0;
		delta = 0;
		fps = 60.f;
		timePerFrame = 1000.0f / FPS_LIMIT;

		// Set seed of rand() function based on current time
		srand(time(NULL));
	}

	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		// Shutdown
		// Application will stop doing brrrrrrrrrr
	}


	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(0);
	
		// Calculate time between frames
		if (!startTime)
			startTime = SDL_GetTicks();
		else
			delta = endTime - startTime;

		// Delay loop to achieve a constant time between frames
		if (delta < timePerFrame)
			SDL_Delay(timePerFrame - delta);

		// Calculate fps for display
		if (delta > timePerFrame)
			fps = 1000.f / delta;

		// Switch between scenes based on gameState
		switch (gameState)
		{
		case GameState_MainMenu:
			Menu();
			break;
		case GameState_InGame:
			InGame(delta);
			break;
		case GameState_GameOver:
			GameOver();
			break;
		default:
			break;
		}

		// GUI
		GUI();

		// Set start values to calculate fps next loop
		startTime = endTime;
		endTime = SDL_GetTicks();
	}


	// -----------------------------------------------------------
	// Application Menu scene
	// -----------------------------------------------------------
	void Game::Menu() {
		// Start game
		if (isShooting) {
			spaceShip.position = { SCRWIDTH / 2, SCRHEIGHT / 2 };				// Set player position to middle of the screen
			spaceShip.rotation = 270;											// Set player rotation facing up

			gameState = 1;														// Set gameState to 1 (inGame)
			screen->Clear(0);
			textPos = { SCRWIDTH / 2,SCRHEIGHT / 5 };
			render.Text("player 1", 8, textPos, scoreScale, 0xFFFFFF, true);
			GUI();
		}
	}


	// -----------------------------------------------------------
	// Application InGame scene
	// -----------------------------------------------------------
	bool initGame = true;
	void Game::InGame(float deltaTime)
	{

		// Start of game
		if (initGame) 
		{
			SDL_Delay(2000);
			initGame = false;
			isShooting = false;

			// Spawn Start Asteroids
			for (int i = 0; i < ASTEROID_START_AMOUNT; i++) 
			{
				vec2 pos = MakeSpawnPos();
				entityManager.CreateAsteroid(pos, 3, 1);
			}
		}

		if (entityManager.score >= 40000)
			enemy.ChangeSize(0);

		// Wave increase
		if (entityManager.GetAsteroidSize() <= 0) 
		{
			wave++;
			int spawnAmount = ASTEROID_START_AMOUNT + (ASTEROID_WAVE_INCREASE * wave);
			if (spawnAmount > ASTEROID_WAVE_AMOUNT_CAP)
				spawnAmount = ASTEROID_WAVE_AMOUNT_CAP;

			// Spawn Asteroids
			for (int i = 0; i < spawnAmount; i++)
			{
				vec2 pos = MakeSpawnPos();
				entityManager.CreateAsteroid(pos, 3, 1);
			}
		}

		// Increase health each time player reaches a score
		if ((entityManager.score - prevScore) > SCORE_HEALTH_INCREASE )
		{
			if (spaceShip.health < 5)
			{
				spaceShip.health++;
			}
			prevScore = entityManager.score;
		}

		// Update current time
		currentTime = SDL_GetTicks();

		// When the player isn't respawning
		if (!isRespawning) 		
		{
			// Update player
			spaceShip.Update(deltaTime);
			spaceShip.Input(isTurningRight, isTurningLeft, isBoosting, isShooting, isWarping);
			if(spaceShip.shoot)
				entityManager.CreateBullet(spaceShip);
			entityManager.Collision(spaceShip,enemy);

			// When asteroid collides with player or saucer bullet with player
			if (entityManager.asteroidPlayerCollision || enemy.Collision(spaceShip))
			{
				entityManager.CreateParticle(spaceShip.position);
				entityManager.CreateParticle(spaceShip.position);
				entityManager.asteroidPlayerCollision = false;
				spaceShip.health--;

				// Check if gameover
				if (spaceShip.health <= 0) {
					gameState = GameState_GameOver;
				}

				isRespawning = true;
				timeOnRespawn = SDL_GetTicks();
			}
		}

		// Check when to respawn player
		if (isRespawning && (currentTime - timeOnRespawn) > RESPAWN_DELAY) 
		{
			// display text to press space to respawn
			textPos.Set(SCRWIDTH / 2, SCRHEIGHT / 2);
			render.Text("press space to respawn", 23, textPos, scoreScale, 0xFFFFFF, true);

			// Wait for space press
			if (isShooting) 
			{
				spaceShip.Respawn();
				spaceShip.SetLastTimeShooting(SDL_GetTicks());
				isRespawning = false;
			}
		}
		entityManager.Update();
		enemy.Update(delta, spaceShip);
	}

	// -----------------------------------------------------------
	// Application GameOver scene
	// -----------------------------------------------------------

	bool isNewHighscore = false;
	bool pressedNext = false;
	bool pressedLeft = false;
	bool pressedRight = false;
	int cursorPos = 0;
	char charLoop[36] = { 'a', 'b', 'c', 'd', 'e', 'f','g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	int charLoopPos;
	char initials[3] = { '_','_','_' };
	bool initGameOver = true;

	void Game::GameOver() 
	{
		if (initGameOver) 
		{
			screen->Clear(0);
			initGameOver = false;
			initGame = true;
			isRespawning = false;

			spaceShip.Reset();
			entityManager.DestroyAll();

			// Check if highscore board is full
			if (highscoresSize < MAX_HIGHSCORE_SLOTS)
			{
				isNewHighscore = true;
			}
			else 
			{
				// Check if its a new highscore
				for (int i = 0; i < highscoresSize; i++)
				{
					if (entityManager.score >= highscores[i].score)
						isNewHighscore = true;
					else
						isNewHighscore = false;
				}
			}
		}

		// Right score
		vec2 textPos = { (SCRWIDTH / 6) * 5, 30 };
		render.Text("00", 2, textPos, scoreScale, 0xFFFFFF, true);

		if (isNewHighscore) 
		{
			// Display gameover info of inputting your highscore
			textPos = { SCRWIDTH / 12, SCRHEIGHT / 4 };
			render.Text("your score is one of the ten best", 36, textPos, textScale, 0xFFFFFF, false);
			textPos.y += 4 * TEXT_SCALE;
			render.Text("please enter your initials", 27, textPos, textScale, 0xFFFFFF, false);
			textPos.y += 4 * TEXT_SCALE;
			render.Text("push arrow keys to select letter", 44, textPos, textScale, 0xFFFFFF, false);
			textPos.y += 4 * TEXT_SCALE;
			render.Text("push return when letter is correct", 35, textPos, textScale, 0xFFFFFF, false);

			// Initials input
			textPos = { SCRWIDTH / 2, (SCRHEIGHT / 3) * 2 };
			render.Text(initials, 3, textPos, textScale * 2, 0xFFFFFF, true);

			// Scroll up alphabet array
			if (isTurningRight && !pressedRight) 
			{
				pressedRight = true;
				if (charLoopPos == 35)
					charLoopPos = 0;
				else
					charLoopPos++;
			}
			else if (!isTurningRight)
				pressedRight = false;

			// Scroll down alphabet array
			if (isTurningLeft && !pressedLeft)
			{
				pressedLeft = true;
				if (charLoopPos == 0)
					charLoopPos = 35;
				else
					charLoopPos--;
			}
			else if (!isTurningLeft)
				pressedLeft = false;

			// Display selected letter/number
			initials[cursorPos] = charLoop[charLoopPos];

			// Go to next initial
			if (isWarping && !pressedNext)
			{
				// If finished save highscore
				if (cursorPos == 2) 
				{
					// Add new highscore
					HighscoreData tmpData;
					tmpData.score = entityManager.score;
					for (int i = 0; i < 3; i++)
					{
						tmpData.initials[i] = initials[i];
					}
					AddHighscore(tmpData);
					
					// Reset initials input values
					cursorPos = 0;
					charLoopPos = 0;
					for (int i = 0; i < 3; i++)
					{
						initials[i] = '_';
					}

					// Go back to main menu
					gameState = GameState_MainMenu;
					initGameOver = true;

					// Reset game values
					entityManager.score = 0;
					wave = 0;
					prevScore = 0;
				}
				else 
					cursorPos++;

				pressedNext = true;
			}
			else if (!isWarping)
				pressedNext = false;
		}
		else 
		{
			gameState = 0;
		}
	}

	vec2 Game::MakeSpawnPos()
	{
		vec2 pos = { 0,0 };

		int maxCycles = 0;
		while (true && maxCycles < 100) {
			maxCycles++;
			switch (rand() % 4) {
				// Top
			case 0:
				pos.Set((rand() % SCRWIDTH + 1), 0);
				break;

				// Bottom
			case 1:
				pos.Set((rand() % SCRWIDTH + 1), SCRHEIGHT);
				break;

				// Left
			case 2:
				pos.Set(0, (rand() % SCRHEIGHT + 1));
				break;

				// Right
			case 3:
				pos.Set(SCRWIDTH, (rand() % SCRHEIGHT + 1));
				break;
			default:
				break;
			}

			if (math::Dist(pos, spaceShip.position) <= MIN_DIST_FROM_PLAYER_TO_SPAWN)
				break;
		}

		return pos;
	}

	void Game::AddHighscore(HighscoreData& _highscoreData)
	{
		HighscoreData newArray[MAX_HIGHSCORE_SLOTS];
		int replaceAtIndex = 0;
		for (int i = 0; i < MAX_HIGHSCORE_SLOTS; i++)
		{
			if (_highscoreData.score >= highscores[i].score) 
			{
				replaceAtIndex = i;
				break;
			}
		}

		for (int i = 0; i < MAX_HIGHSCORE_SLOTS; i++)
		{
			if (i < replaceAtIndex)
				newArray[i] = highscores[i];
			else if (i == replaceAtIndex)
				newArray[i] = _highscoreData;
			else
				newArray[i] = highscores[i - 1];
		}

		for (int i = 0; i < MAX_HIGHSCORE_SLOTS; i++)
		{
			highscores[i] = newArray[i];
		}

		if (highscoresSize < MAX_HIGHSCORE_SLOTS)
			highscoresSize++;
	}

	// -----------------------------------------------------------
	// Application GUI
	// -----------------------------------------------------------
	void Game::GUI() 
	{
		// GUI in menu
		if (gameState == 0) 
		{
			// Right score
			textPos = { (SCRWIDTH / 6) * 5, 30 };
			render.Text("00", 2, textPos, scoreScale, 0xFFFFFF, true);

			// 1 coin 1 play
			textPos = { SCRWIDTH / 2,(SCRHEIGHT / 5) * 4 };
			render.Text("1 coin 1 play", 13, textPos, scoreScale, 0xFFFFFF, true);

			if (highscoresSize > 0) {
				// HighScore Text
				textPos = { SCRWIDTH / 2,SCRHEIGHT / 5 };
				render.Text("high scores", 11, textPos, scoreScale, 0xFFFFFF, true);

				textPos = { SCRWIDTH / 2, SCRHEIGHT / 5};
				// Draw highscores
				for (int i = 0; i < highscoresSize; i++)
				{
					textPos.x = (SCRWIDTH / 3) - 20;
					textPos.y += 20;
					// Draw number
					render.Number(i + 1, textPos, highscoreScale, 0xFFFFFF, true);

					textPos.x = SCRWIDTH / 2;
					// Draw score
					render.Number(highscores[i].score, textPos, highscoreScale, 0xFFFFFF, true);

					textPos.x = ((SCRWIDTH / 3) * 2) - 20;
					// Draw initials
					render.Text(highscores[i].initials, 3, textPos, highscoreScale, 0xFFFFFF, true);

				}
			}
		}

		//GUI in game
		if (gameState == 1) 
		{
			vec2 healthPos = { SCRWIDTH / 8 ,60};
			for (int i = 0; i < spaceShip.health; i++) 
			{
				render.Draw(spaceShip.polygon, spaceShip.polygonSize, healthPos.x,	healthPos.y, 270, highscoreScale);
				healthPos.x += 5 * HIGHSCORE_SCALE;
			}
		}

		// Display left score or place holder
		textPos = { SCRWIDTH / 6, 30 };
		if (entityManager.score >= 1)
		{
			render.Number(entityManager.score, textPos, scoreScale, 0xFFFFFF, true);
		}
		else
			render.Text("00", 2, textPos, scoreScale, 0xFFFFFF, true);

		// Display Highscore or place holder
		textPos = { SCRWIDTH / 2, 20 };
		if (highscoresSize > 0) 
		{
			// Display highscore
			for (int i = 0; i < highscoresSize; i++)
			{
				// Draw score
				render.Number(highscores[0].score, textPos, highscoreScale, 0xFFFFFF, true);
			}
		}
		else
			render.Text("00", 2, textPos, highscoreScale, 0xFFFFFF, true);

		// Copyrights Text
		textPos = { SCRWIDTH / 2, SCRHEIGHT - 20 };
		render.Text("2020 joey inc", 13, textPos, highscoreScale, 0xFFFFFF, true);
	}
};
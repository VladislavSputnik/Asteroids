#pragma once
#include "player.h"
#include "bullet.h"
#include "asteroid.h"
#include "particle.h"
#include "saucer.h"
#include "entitymanager.h"

// Keycodes
enum KeyCode {
	SPACE = 44,
	RETURN = 40,
	ARROW_UP = 82,
	ARROW_LEFT = 80,
	ARROW_RIGHT = 79
};

// Gamestates
enum GameStates {
	GameState_MainMenu = 0,
	GameState_InGame = 1,
	GameState_GameOver = 2
};

#define FPS_LIMIT 60

// Gameplay
#define RESPAWN_DELAY 3000							// Miliseconds delay before respawn
#define HYPERSPACE_DIST 100
#define HYPERSPACE_INVERVAL 10000					// Miliseconds interval between hyperspaces
#define SCORE_HEALTH_INCREASE 10000					// Amount of points needed before your health increases

// Bullet behaviour
#define BULLET_INTERVAL 200							// Miliseconds interval between shots

// Asteroid behaviour
#define ASTEROID_START_AMOUNT 4
#define ASTEROID_WAVE_INCREASE 2
#define ASTEROID_WAVE_AMOUNT_CAP 11
#define MIN_DIST_FROM_PLAYER_TO_SPAWN 50            // Minimal distant from a player to spawn a asteroid

// Highscore
#define MAX_HIGHSCORE_SLOTS 10						// The max amount of highscore that can be stored

// GUI text scale
#define TEXT_SCALE 6
#define SCORE_SCALE 8
#define HIGHSCORE_SCALE 3

namespace Tmpl8 {

class Game
{
public:
	// Highscore Struct
	struct HighscoreData {
		int score = 0;
		char initials[3];
	};

	// Functions
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );

	// Scenes
	void Menu();
	void InGame(float deltaTime);
	void GameOver();

	// Spawn handling
	vec2 MakeSpawnPos();
	void AddHighscore(HighscoreData& _highscoreData);

	// GUI
	void GUI();

	// Input
	void KeyUp(unsigned int _key) {
		switch (_key) {
		case SPACE:
			isShooting = false;
			break;
		case RETURN:
			isWarping = false;
			break;
		case ARROW_UP:
			isBoosting = false;
			break;
		case ARROW_LEFT:
			isTurningLeft = false;
			break;
		case ARROW_RIGHT:
			isTurningRight = false;
			break;
		default:
			break;
		}
	};
	void KeyDown(unsigned int _key) {
		switch (_key) {
		case SPACE:
			isShooting = true;
			break;
		case RETURN:
			isWarping = true;
			break;
		case ARROW_UP:
			isBoosting = true;
			break;
		case ARROW_LEFT:
			isTurningLeft = true;
			break;
		case ARROW_RIGHT:
			isTurningRight = true;
			break;
		default:
			break;
		}
	};

	// Rendering
	Surface* screen;								// Surface to render to
	render render;									// Render object to use render functions

	// Objects
	entitymanager entityManager;
	player spaceShip;								// Player object
	saucer enemy;

	// Game data
	int gameState;									// Gamestate: 0->Menu; 1->InGame; 2->GameOver
	int timeOnRespawn;								// Get time on death
	int currentTime;								// Current time (used for shootinh cooldown)	
	int wave;                                       // Current wave
	int prevScore;									// Previous score
	bool isRespawning;								// If the player is respawning

	// Highscore data
	HighscoreData highscores[MAX_HIGHSCORE_SLOTS];	// Highscore saving array
	int highscoresSize;								// Amount of highscore slots being used

	// GUI data
	vec2 textScale;									// Scale of text being displayed
	vec2 scoreScale;								// Scale of score being displayed
	vec2 highscoreScale;							// Scale of highscore being displayed
	vec2 textPos;									// Position of text

	// Debug
	bool debugToggle;								// Toggles debug overlay on / off
	bool isDown;									// Boolean to check if debug key is down

	// Input
	bool isBoosting;								// Is player boosting
	bool isShooting;								// Is player shooting
	bool isWarping;									// Is player warping
	bool isTurningLeft;								// Is player turning left
	bool isTurningRight;							// Is player turning right

private:
	// Frame data
	int startTime;									// Start time of fps measurement
	int endTime;									// End time of fps measurement
	int delta;										// Difference between start and end time
	float fps;										// Current fps
	float timePerFrame;								// Time per frame
};

}; // namespace Tmpl8
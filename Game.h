/**
*
* Solution to course project #5
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Filip Aleksandrov Andonov
* @idnumber 2MI0600320
* @compiler VC
*
* Game loading and main game loop
*
*/

#pragma once
#include "GhostsTracking.h"
#include "HandleConsole.h"

constexpr int GAME_TURN_MILLISECONDS = 300;
constexpr int INPUT_REFRESH_MILLISECONDS = 10;

constexpr int ACTIVATION_BLINKY = 0;
constexpr int ACTIVATION_PINKY = 20;
constexpr int ACTIVATION_INKY = 40;
constexpr int ACTIVATION_CLYDE = 60;

constexpr int TIME_IN_FRIGHTEN_MODE = 10;
constexpr int PAC_MAN_MOVES_IN_FRIGHTEN_MODE = 2;

constexpr int SECONDS_BEFORE_THE_GAME_STARTS = 3;

enum class GameMode
{
	ChaseMode,
	FrightenedMode
};

struct Game
{
	Map map;

	GameMode mode = GameMode::ChaseMode;
	int turnsInFrightenMode = 0;

	int maxScore;
	int score = 0;
	int result = 0;

	Entity pacMan;
	Entity blinky;
	Entity pinky;
	Entity inky;
	Entity clyde;
	Position respawnBlinky;
	Position respawnPinky;
	Position respawnInky;
	Position respawnClyde;
};

MapErrorCode loadGame(const char* fileName, Game& game);
void runGame(Game& game);

void setUpEntities(Game& game);
Entity getEntityInMap(Map& map, char entityCharacter);
Position getPositionInMap(const Map& map, char entityCharacter);
Position getNearestValidPosition(const Map& map, const Position& position);

void waitSomeTimeForInput(Entity& pacMan, int refreshRateMilliseconds, int durationMilliseconds);
void movePacMan(Game& game, Entity** ghosts, const Position* respawnPositions);

void moveGhostsInChaseMode(Game& game, const Entity** ghosts);
void moveGhostsInFrightenedMode(Game& game, Entity** ghosts, const Position* respawnPositions);
void turnAroundGhosts(Game& game, Entity** ghosts, const Position* respawnPositions);
void turnAroundGhost(Entity& ghost, int score, int activationScore);

bool hasPacManCollidedWithGhost(const Entity& pacMan, const Entity** ghosts, int ghostCount);
void killGhostsColidedWithPacMan(const Entity& pacMan, Entity** ghosts,
	const Position* respawnPositions, int ghostCount);

void countdownBeforeStart(int seconds);
void printGame(const Game& game);
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
* Implementation of Game.h
*
*/
#include "Game.h"
#include <iostream>
#include <windows.h>

MapErrorCode loadGame(const char* fileName, Game& game)
{
	MapErrorCode errorCode = readMap(fileName, game.map.grid, game.map.xSize, game.map.ySize);
	if (errorCode != MapErrorCode::Okay)
		return errorCode;

	setUpEntities(game);
	game.maxScore = getMapMaxScore(game.map.grid, game.map.xSize, game.map.ySize);
	return MapErrorCode::Okay;
}

void runGame(Game& game)
{
	Entity* ghosts[GHOST_COUNT] = { &game.blinky, &game.pinky, &game.inky, &game.clyde };
	const Position respawnPositions[GHOST_COUNT] = { game.respawnBlinky, game.respawnPinky,
		game.respawnInky, game.respawnClyde };

	setConsoleCursorVisibility(false);
	countdownBeforeStart(SECONDS_BEFORE_THE_GAME_STARTS);
	while (game.result == 0)
	{
		printGame(game);

		if (game.mode == GameMode::ChaseMode)
		{
			waitSomeTimeForInput(game.pacMan, INPUT_REFRESH_MILLISECONDS, GAME_TURN_MILLISECONDS);
			movePacMan(game, ghosts, respawnPositions);
			if (game.result != 0)
				break;

			if (game.mode == GameMode::FrightenedMode)
				turnAroundGhosts(game, ghosts, respawnPositions);
			else
				moveGhostsInChaseMode(game, (const Entity**)ghosts);
		}
		else
		{
			for (int i = 0; i < PAC_MAN_MOVES_IN_FRIGHTEN_MODE; i++)
			{
				waitSomeTimeForInput(game.pacMan, INPUT_REFRESH_MILLISECONDS, 
					GAME_TURN_MILLISECONDS / PAC_MAN_MOVES_IN_FRIGHTEN_MODE);
				movePacMan(game, ghosts, respawnPositions);
				if (game.result != 0)
					break;

				if (i != PAC_MAN_MOVES_IN_FRIGHTEN_MODE - 1)
					printGame(game);
			}
			if (game.result != 0)
				break;

			moveGhostsInFrightenedMode(game, ghosts, respawnPositions);

			game.turnsInFrightenMode--;
			if (game.turnsInFrightenMode == 0)
				game.mode = GameMode::ChaseMode;
		}	
	}
	printGame(game);

	prepareConsole(game.map.xSize);
	printResultMessage(game.result);
}

void moveGhostsInChaseMode(Game& game, const Entity** ghosts)
{
	if (game.score >= ACTIVATION_BLINKY)
		trackingBlinky(game.blinky, game.pacMan, game.map, ghosts, GHOST_COUNT);
	if (game.score >= ACTIVATION_PINKY)
		trackingPinky(game.pinky, game.pacMan, game.map, ghosts, GHOST_COUNT);
	if (game.score >= ACTIVATION_INKY)
		trackingInky(game.inky, game.pacMan, game.blinky, game.map, ghosts, GHOST_COUNT);
	if (game.score >= ACTIVATION_CLYDE)
		trackingClyde(game.clyde, game.pacMan, game.respawnClyde, game.map, ghosts, GHOST_COUNT);

	if (hasPacManCollidedWithGhost(game.pacMan, ghosts, GHOST_COUNT))
		game.result = -1;
}

void moveGhostsInFrightenedMode(Game& game, Entity** ghosts, const Position* respawnPositions)
{
	if (game.score >= ACTIVATION_BLINKY)
		moveGhostRandomly(game.blinky, game.map, (const Entity**)ghosts, GHOST_COUNT);
	if (game.score >= ACTIVATION_PINKY)
		moveGhostRandomly(game.pinky, game.map, (const Entity**)ghosts, GHOST_COUNT);
	if (game.score >= ACTIVATION_INKY)
		moveGhostRandomly(game.inky, game.map, (const Entity**)ghosts, GHOST_COUNT);
	if (game.score >= ACTIVATION_CLYDE)
		moveGhostRandomly(game.clyde, game.map, (const Entity**)ghosts, GHOST_COUNT);

	killGhostsColidedWithPacMan(game.pacMan, ghosts, respawnPositions, GHOST_COUNT);
}

void turnAroundGhosts(Game& game, Entity** ghosts, const Position* respawnPositions)
{
	turnAroundGhost(game.blinky, game.score, ACTIVATION_BLINKY);
	turnAroundGhost(game.pinky, game.score, ACTIVATION_PINKY);
	turnAroundGhost(game.inky, game.score, ACTIVATION_INKY);
	turnAroundGhost(game.clyde, game.score, ACTIVATION_CLYDE);
	
	killGhostsColidedWithPacMan(game.pacMan, ghosts, respawnPositions, GHOST_COUNT);
}

void turnAroundGhost(Entity& ghost, int score, int activationScore)
{
	if (score >= activationScore)
	{
		turnEntityAround(ghost);
		moveEntity(ghost);
	}
}

void printGame(const Game& game)
{
	printGameWithoutEntities(game.map, game.score, game.maxScore);
	printEntities(game.pacMan, game.blinky, game.pinky, game.inky, game.clyde, game.mode == GameMode::ChaseMode);
}

void setUpEntities(Game& game)
{
	game.pacMan = getEntityInMap(game.map, PAC_MAN_SYMBOL);
	game.blinky = getEntityInMap(game.map, BLINKY_SYMBOL);
	game.pinky = getEntityInMap(game.map, PINKY_SYMBOL);
	game.inky = getEntityInMap(game.map, INKY_SYMBOL);
	game.clyde = getEntityInMap(game.map, CLYDE_SYMBOL);

	const Position upperLeftCorner{ 0, 0 };
	const Position upperRightCorner{ 0, game.map.ySize - 1 };
	const Position lowerLeftCorner{ game.map.xSize - 1, 0 };
	const Position lowerRightCorner{ game.map.xSize - 1, game.map.ySize - 1 };

	game.respawnBlinky = getNearestValidPosition(game.map, upperRightCorner);
	game.respawnPinky = getNearestValidPosition(game.map, upperLeftCorner);
	game.respawnInky = getNearestValidPosition(game.map, lowerRightCorner);
	game.respawnClyde = getNearestValidPosition(game.map, lowerLeftCorner);
}

Entity getEntityInMap(Map& map, char entityCharacter)
{
	Position pos = getPositionInMap(map, entityCharacter);
	map.grid[pos.x][pos.y] = EMPTY_SYMBOL;
	return Entity{ pos };
}

Position getPositionInMap(const Map& map, char entityCharacter)
{
	for (int i = 0; i < map.xSize; i++)
	{
		for (int j = 0; j < map.ySize; j++)
		{
			if (map.grid[i][j] == entityCharacter)
				return { i, j };
		}
	}
	return { -1, -1 };
}

Position getNearestValidPosition(const Map& map, const Position& position)
{
	if (!isWall(map.grid[position.x][position.y]))
		return position;

	int minDis = BIG_DISTANCE;
	Position nearest{};
	for (int i = 0; i < map.xSize; i++)
	{
		for (int j = 0; j < map.ySize; j++)
		{
			if (isWall(map.grid[i][j]))
				continue;

			Position cur = { i, j };
			int dis = getDistanceSquared(cur, position);
			if (dis < minDis)
			{
				minDis = dis;
				nearest = cur;
			}
		}
	}
	return nearest;
}

bool hasPacManCollidedWithGhost(const Entity& pacMan, const Entity** ghosts, int ghostCount)
{
	for (int i = 0; i < ghostCount; i++)
	{
		if (areEqual(pacMan.position, ghosts[i]->position))
			return true;
	}
	return false;
}

void killGhostsColidedWithPacMan(const Entity& pacMan, Entity** ghosts, 
	const Position* respawnPositions, int ghostCount)
{
	for (int i = 0; i < ghostCount; i++)
	{
		if (areEqual(pacMan.position, ghosts[i]->position))
			ghosts[i]->position = respawnPositions[i];
	}
}

void movePacMan(Game& game, Entity** ghosts, const Position* respawnPositions)
{
	Position pos = game.pacMan.position;
	moveInDirection(pos, game.pacMan.direction);
	if (isValidCoordinate(pos.x, game.map.xSize) && isValidCoordinate(pos.y, game.map.ySize) 
		&& !isWall(game.map.grid[pos.x][pos.y]))
	{
		moveEntity(game.pacMan);

		if (game.mode == GameMode::ChaseMode && 
			hasPacManCollidedWithGhost(game.pacMan, (const Entity**)ghosts, GHOST_COUNT))
		{
			game.result = -1;
			return;
		}

		if (game.mode == GameMode::FrightenedMode)
			killGhostsColidedWithPacMan(game.pacMan, ghosts, respawnPositions, GHOST_COUNT);

		if (isFood(game.map.grid[pos.x][pos.y]))
		{
			if (isSuperFood(game.map.grid[pos.x][pos.y]))
			{
				game.mode = GameMode::FrightenedMode;
				game.turnsInFrightenMode += TIME_IN_FRIGHTEN_MODE;
			}
			game.map.grid[pos.x][pos.y] = EMPTY_SYMBOL;
			game.score++;
			if (game.score == game.maxScore)
				game.result = 1;
		}
	}
}

void countdownBeforeStart(int seconds)
{
	constexpr int SECOND_IN_MILLISECONDS= 1000;
	while (seconds > 0)
	{
		resetCursorPosition();
		std::cout << seconds;
		seconds--;
		Sleep(SECOND_IN_MILLISECONDS);
	}
}

void waitSomeTimeForInput(Entity& pacMan, int refreshRateMilliseconds, int durationMilliseconds)
{
	int milliseconds = 0;
	while (milliseconds < durationMilliseconds)
	{
		updatePacManDirection(pacMan);
		Sleep(refreshRateMilliseconds);
		milliseconds += refreshRateMilliseconds;
	}
}

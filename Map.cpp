#include "Map.h"
#include <iostream>

void printMapErrorMessage(MapErrorCode errorCode)
{
	if (errorCode == MapErrorCode::Okay)
		return;

	const char* message;
	switch (errorCode)
	{
	case MapErrorCode::NullFileName:
		message = NULL_FILE_NAME_GIVEN_MESSAGE;
		break;
	case MapErrorCode::FileDoesNotOpen:
		message = FILE_DOES_NOT_OPEN_MESSAGE;
		break;
	case MapErrorCode::InvalidMapSize:
		message = INVALID_MAP_SIZE_MESSAGE;
		break;
	case MapErrorCode::InvalidCharacter:
		message = INVALID_CHARACTER_IN_MAP_MESSAGE;
		break;
	case MapErrorCode::NotExactlyOneOfEachEntities:
		message = NOT_EXACTLY_ONE_OF_EACH_ENTITIES_MESSAGE;
		break;
	case MapErrorCode::NotSymetrical:
		message = NOT_SYMETRICAL_MAP_MESSAGE;
		break;
	case MapErrorCode::GhostsNotInCage:
		message = GHOSTS_NOT_IN_CAGE_MESSAGE;
		break;
	default:
		message = "Unexpected error occurred!";
		break;
	}
	std::cout << message << '\n';
}

MapErrorCode readMap(const char* fileName, char map[][MAP_MAX_SIZE], int& xSize, int& ySize)
{
	if (!fileName)
		return MapErrorCode::NullFileName;

	std::ifstream ifs(fileName);
	if (!ifs.is_open())
		return MapErrorCode::FileDoesNotOpen;

	ifs >> xSize >> ySize;
	if (!isValidMapSize(xSize, ySize))
		return MapErrorCode::InvalidMapSize;

	MapErrorCode errorCode = readMap(ifs, map, xSize, ySize);
	if (errorCode != MapErrorCode::Okay)
		return errorCode;
	
	if (!hasMapOnlyOneOfEachEntities(map, xSize, ySize))
		return MapErrorCode::NotExactlyOneOfEachEntities;

	if (!isSymetricalMap(map, xSize, ySize))
		return MapErrorCode::NotSymetrical;
	if (!hasMapCage(map, xSize, ySize))
		return MapErrorCode::GhostsNotInCage;

	return MapErrorCode::Okay;
}

MapErrorCode readMap(std::ifstream& ifs, char map[][MAP_MAX_SIZE], int xSize, int ySize)
{
	ifs.ignore();
	for (int i = 0; i < xSize; i++)
	{
		MapErrorCode errorCode = readMapRow(ifs, map[i], ySize);
		if (errorCode != MapErrorCode::Okay)
			return errorCode;

		if (ifs.eof() && i != xSize - 1 || !ifs.eof() && i == xSize - 1)
			return MapErrorCode::InvalidMapSize;
	}
	return MapErrorCode::Okay;
}

MapErrorCode readMapRow(std::ifstream& ifs, char row[], int rowSize)
{
	int index = 0;
	while (true)
	{
		char ch;
		ifs.get(ch);

		if (ifs.eof() || ch == '\n')
		{
			if (index != rowSize)
				return MapErrorCode::InvalidMapSize;

			return MapErrorCode::Okay;
		}

		if (index == rowSize)
			return MapErrorCode::InvalidMapSize;

		if (!isValidCharacter(ch))
			return MapErrorCode::InvalidCharacter;

		row[index++] = ch;
	}
}

bool isValidMapSize(int xSize, int ySize)
{
	return xSize > 0 && xSize <= MAP_MAX_SIZE && ySize > 0 && ySize <= MAP_MAX_SIZE;
}

bool hasMapOnlyOneOfEachEntities(const char map[][MAP_MAX_SIZE], int xSize, int ySize)
{
	bool entities[ENTITIES_COUNT]{};
	int sum = 0;
	for (int i = 0; i < xSize; i++)
	{
		for (int j = 0; j < ySize; j++)
		{
			if (!isEntity(map[i][j]))
				continue;

			if (!visitEntity(map[i][j], entities))
				return false;
			sum++;
		}
	}
	return sum == ENTITIES_COUNT;
}

bool visitEntity(char ch, bool* entities)
{
	switch (ch)
	{
	case PAC_MAN_SYMBOL:
		return visitEntity(entities);
	case BLINKY_SYMBOL:
		return visitEntity(entities + 1);
	case PINKY_SYMBOL:
		return visitEntity(entities + 2);
	case INKY_SYMBOL:
		return visitEntity(entities + 3);
	case CLYDE_SYMBOL:
		return visitEntity(entities + 4);
	default:
		return true;
	}
}

bool visitEntity(bool* ptr)
{
	if (*ptr)
		return false;
	return *ptr = true;
}

bool isSymetricalMap(const char map[][MAP_MAX_SIZE], int xSize, int ySize)
{
	for (int i = 0; i < xSize; i++)
	{
		for (int j = 0; j < ySize / 2; j++)
		{
			char symbol = map[i][j];
			char mirrorSymbol = map[i][ySize - j - 1];

			if (isGhost(symbol) && isGhost(mirrorSymbol))
				continue;

			if (symbol != mirrorSymbol)
				return false;
		}
	}
	return true;
}

bool hasMapCage(const char map[][MAP_MAX_SIZE], int xSize, int ySize)
{
	for (int i = 1; i < xSize - 1; i++)
	{
		for (int j = 0; j < ySize - 1; j++)
		{
			if (isGhost(map[i][j]))
				return hasUpwardsMapCage(map, xSize, ySize, i, j) || 
				       hasDownwardsMapCage(map, xSize, ySize, i + 1, j + 1);
		}
	}
	return false;
}

bool hasUpwardsMapCage(const char map[][MAP_MAX_SIZE], int xSize, int ySize, int x, int y)
{
	if (!isMoovableForGhost(map[x - 1][y]))
		return false;

	if (!isValidCoordinate(x + 2, xSize) || !isValidCoordinate(y - 2, ySize) || 
	    !isValidCoordinate(y + 2, ySize))
		return false;

	for (int i = y - 2; i <= y + 2; i++)
	{
		if (i != y && !isWall(map[x][i]))
			return false;
	}

	if (!isWall(map[x + 1][y - 2]) && !isWall(map[x + 1][y + 2]))
		return false;
	for (int i = y - 1; i <= y + 1; i++)
	{
		if (!isGhost(map[x + 1][i]))
			return false;
	}


	for (int i = y - 2; i <= y + 2; i++)
	{
		if (!isWall(map[x + 2][i]))
			return false;
	}

	return true;
}

bool hasDownwardsMapCage(const char map[][MAP_MAX_SIZE], int xSize, int ySize, int x, int y)
{
	if (!isValidCoordinate(x + 1, xSize) || !isMoovableForGhost(map[x + 1][y]) || !isGhost(map[x][y]))
		return false;

	if (!isValidCoordinate(y - 2, ySize) || !isValidCoordinate(y + 2, ySize))
		return false;

	for (int i = y - 2; i <= y + 2; i++)
	{
		if (!isWall(map[x - 2][i]))
			return false;
	}

	if (!isWall(map[x - 1][y - 2]) && !isWall(map[x - 1][y + 2]))
		return false;
	for (int i = y - 1; i <= y + 1; i++)
	{
		if (!isGhost(map[x - 1][i]))
			return false;
	}

	for (int i = y - 2; i <= y + 2; i++)
	{
		if (i != y && !isWall(map[x][i]))
			return false;
	}

	return true;
}

bool isValidCoordinate(int value, int maxValue)
{
	return value >= 0 && value < maxValue;
}

int getMapMaxScore(const char map[][MAP_MAX_SIZE], int xSize, int ySize)
{
	int score = 0;
	for (int i = 0; i < xSize; i++)
	{
		for (int j = 0; j < ySize; j++)
		{
			score += isFood(map[i][j]);
		}
	}
	return score;
}

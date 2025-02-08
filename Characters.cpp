#include "Characters.h"
#include <iostream>

bool isEntity(char ch)
{
	return isPacMap(ch) || isGhost(ch);
}

bool isPacMap(char ch)
{
	return ch == PAC_MAN_SYMBOL;
}

bool isGhost(char ch)
{
	switch (ch)
	{
	case BLINKY_SYMBOL:
	case PINKY_SYMBOL:
	case INKY_SYMBOL:
	case CLYDE_SYMBOL:
		return true;
	default:
		return false;
	}
}

bool isWall(char ch)
{
	return ch == WALL_SYMBOL;
}

bool isFood(char ch)
{
	return ch == FOOD_SYMBOL || isSuperFood(ch);
}

bool isSuperFood(char ch)
{
	return ch == SUPER_FOOD_SYMBOL;
}

bool isEmptySpace(char ch)
{
	return ch == EMPTY_SYMBOL;
}

bool isValidCharacter(char ch)
{
	return isEntity(ch) || isWall(ch) || isFood(ch) || isEmptySpace(ch);
}

bool isMoovableForGhost(char ch)
{
	return !isWall(ch) && !isGhost(ch);
}
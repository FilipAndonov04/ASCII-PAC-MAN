#pragma once
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
* Map functions: reading map from file and validation, error messages
*
*/

#include "Characters.h"
#include <fstream>

constexpr int MAP_MAX_SIZE = 50;

struct Map
{
	char grid[MAP_MAX_SIZE][MAP_MAX_SIZE]{};
	int xSize;
	int ySize;
};

constexpr int GHOST_COUNT = 4;
constexpr int ENTITIES_COUNT = GHOST_COUNT + 1;

constexpr char NULL_FILE_NAME_GIVEN_MESSAGE[] = "File name cannot be null!";
constexpr char FILE_DOES_NOT_OPEN_MESSAGE[] = "File does not open!";
constexpr char INVALID_MAP_SIZE_MESSAGE[] = "Map size is not valid!";
constexpr char INVALID_CHARACTER_IN_MAP_MESSAGE[] = "Invalid character in map!";
constexpr char NOT_EXACTLY_ONE_OF_EACH_ENTITIES_MESSAGE[] = "There must be exactly one Pac-Man and exatly one of each ghosts!";
constexpr char NOT_SYMETRICAL_MAP_MESSAGE[] = "Map is not symetrical!";
constexpr char GHOSTS_NOT_IN_CAGE_MESSAGE[] = "Ghosts must be in a cage in the beggining of the game!";

enum class MapErrorCode
{
	Okay,
	NullFileName,
	FileDoesNotOpen,
	InvalidMapSize,
	InvalidCharacter,
	NotExactlyOneOfEachEntities,
	NotSymetrical,
	GhostsNotInCage
};
void printMapErrorMessage(MapErrorCode errorCode);

MapErrorCode readMap(const char* fileName, char map[][MAP_MAX_SIZE], int& xSize, int& ySize);
MapErrorCode readMap(std::ifstream& ifs, char map[][MAP_MAX_SIZE], int xSize, int ySize);
MapErrorCode readMapRow(std::ifstream& ifs, char row[], int rowSize);

bool isValidMapSize(int xSize, int ySize);

bool hasMapOnlyOneOfEachEntities(const char map[][MAP_MAX_SIZE], int xSize, int ySize);
bool visitEntity(char ch, bool* arr);
bool visitEntity(bool* ptr);

bool isSymetricalMap(const char map[][MAP_MAX_SIZE], int xSize, int ySize);

bool hasMapCage(const char map[][MAP_MAX_SIZE], int xSize, int ySize);
bool hasUpwardsMapCage(const char map[][MAP_MAX_SIZE], int xSize, int ySize, int x, int y);
bool hasDownwardsMapCage(const char map[][MAP_MAX_SIZE], int xSize, int ySize, int x, int y);
bool isValidCoordinate(int value, int maxValue);

int getMapMaxScore(const char map[][MAP_MAX_SIZE], int xSize, int ySize);
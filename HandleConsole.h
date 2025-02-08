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
* Console printing and input handling
*
*/

#pragma once
#include "Map.h"
#include "Entity.h"

constexpr char KEY_UP = 'W';
constexpr char KEY_LEFT = 'A';
constexpr char KEY_DOWN = 'S';
constexpr char KEY_RIGHT = 'D';

constexpr int INPUT_MASK = 0x8000;

constexpr char COLOUR_BLACK = 0;
constexpr char COLOUR_DARK_BLUE = 1;
constexpr char COLOUR_DARK_GREEN = 2;
constexpr char COLOUR_LIGHT_BLUE = 3;
constexpr char COLOUR_DARK_RED = 4;
constexpr char COLOUR_MAGENTA = 5;
constexpr char COLOUR_ORANGE = 6;
constexpr char COLOUR_LIGHT_GRAY = 7;
constexpr char COLOUR_GRAY = 8;
constexpr char COLOUR_BLUE = 9;
constexpr char COLOUR_GREEN = 10;
constexpr char COLOUR_CYAN = 11;
constexpr char COLOUR_RED = 12;
constexpr char COLOUR_PINK = 13;
constexpr char COLOUR_YELLOW = 14;
constexpr char COLOUR_WHITE = 15;

constexpr char GHOST_FRIGHTENED_COLOUR = COLOUR_LIGHT_BLUE;

constexpr int OFFSET_X = 1;

void setConsoleCursorVisibility(bool isVisible);
void setCursorPosition(int row, int col);
void setConsoleColour(int colourCode);
void resetCursorPosition();
void prepareConsole(int row);

char getColourFromChar(char ch);

void updatePacManDirection(Entity& pacMan);

void printGameWithoutEntities(const Map& map, int score, int maxScore);
void printScore(int score, int maxScore);
void printMap(const Map& map);

void printEntity(const Entity& entity, char sign, bool isChaseMode);
void printEntities(const Entity& pacMan, const Entity& blinky, const Entity& pinky, 
	const Entity& inky, const Entity& clyde, bool isChaseMode);

void printResultMessage(int result);
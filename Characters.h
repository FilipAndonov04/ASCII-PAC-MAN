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
* Game symbols
* 
*/

constexpr char PAC_MAN_SYMBOL = 'Y';
constexpr char BLINKY_SYMBOL = 'B';
constexpr char PINKY_SYMBOL = 'P';
constexpr char INKY_SYMBOL = 'I';
constexpr char CLYDE_SYMBOL = 'C';

constexpr char WALL_SYMBOL = '#';
constexpr char FOOD_SYMBOL = '-';
constexpr char SUPER_FOOD_SYMBOL = '@';
constexpr char EMPTY_SYMBOL = ' ';

bool isEntity(char ch);
bool isPacMap(char ch);
bool isGhost(char ch);
bool isWall(char ch);
bool isFood(char ch);
bool isSuperFood(char ch);
bool isEmptySpace(char ch);
bool isValidCharacter(char ch);
bool isMoovableForGhost(char ch);
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
* Entity and it's direction and position and basic their functions
*
*/

constexpr int DIRECTIONS_COUNT = 4;

enum class Direction
{
	Up,
	Left,
	Down,
	Right
};
Direction getOppositeDirection(Direction direction);

int getAbs(int num);

struct Position
{
	int x;
	int y;
};
bool areEqual(const Position& p1, const Position& p2);
int getDistanceSquared(const Position& p1, const Position& p2);
double getDistance(const Position& p1, const Position& p2);
Position getMirroredPosition(const Position& center, const Position& position);
void moveInDirection(Position& position, Direction direction);
void moveInDirection(Position& position, Direction direction, int count);

struct Entity
{
	Position position;
	Direction direction;
};
void changeEntityDirection(Entity& entity, Direction newDirection);
void moveEntity(Entity& entity);
void turnEntityAround(Entity& entity);
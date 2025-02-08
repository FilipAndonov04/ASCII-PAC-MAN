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
* Ghost movement and tracking of Pac-Man
*
*/

#pragma once
#include "Entity.h"
#include "Map.h"

constexpr int BIG_DISTANCE = MAP_MAX_SIZE * MAP_MAX_SIZE * 10;

constexpr int PINKY_PREDICTION = 4;
constexpr Direction PINKY_SPECIAL_DIRECTION = Direction::Up;
constexpr Direction PINKY_ADDITIONAL_DIRECTION = Direction::Left;

constexpr int INKY_PREDICTION = 2;
constexpr Direction INKY_SPECIAL_DIRECTION = Direction::Up;
constexpr Direction INKY_ADDITIONAL_DIRECTION = Direction::Left;

constexpr int CLYDE_BEHAVIOR_DISTANCE = 8;

Direction directionToShortestPathToTarget(const Entity& ghost, const Position& target, 
	const Map& map, const Entity** ghosts, int ghostCount);

void sortDistances(int* distances, Direction* directions, int size);
bool isValidPosition(const Position& pos, const Map& map, const Entity** ghosts, int ghostCount);
bool isThereOtherGhostOnPosition(const Position& pos, const Entity** ghosts, int ghostCount);

void trackingBlinky(Entity& blinky, const Entity& pacMan, const Map& map, const Entity** ghosts, int ghostCount);
void trackingPinky(Entity& pinky, const Entity& pacMan, const Map& map, const Entity** ghosts, int ghostCount);
void trackingInky(Entity& inky, const Entity& pacMan, const Entity& blinky, const Map& map, 
	const Entity** ghosts, int ghostCount);
void trackingClyde(Entity& clyde, const Entity& pacMan, const Position& clydeFavouriteSpot, 
	const Map& map, const Entity** ghosts, int ghostCount);
void moveGhostToTarget(Entity& ghost, const Position& target, const Map& map, const Entity** ghosts, int ghostCount);

void moveGhostRandomly(Entity& ghost, const Map& map, const Entity** ghosts, int ghostCount);

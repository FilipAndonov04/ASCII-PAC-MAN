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
* Implementation of GhostsTracking.h
*
*/
#include "GhostsTracking.h"
#include <cstdlib>

Direction directionToShortestPathToTarget(const Entity& ghost, const Position& target, 
    const Map& map, const Entity** ghosts, int ghostCount)
{
    Direction directions[DIRECTIONS_COUNT]{};
    int distance[DIRECTIONS_COUNT]{};
    for (int i = 0; i < DIRECTIONS_COUNT; i++)
    {
        directions[i] = (Direction)i;
        if (directions[i] == getOppositeDirection(ghost.direction))
        {
            distance[i] = BIG_DISTANCE - 1;
            continue;
        }

        Position pos = ghost.position;
        moveInDirection(pos, directions[i]);
        if (!isValidPosition(pos, map, ghosts, ghostCount))
            distance[i] = BIG_DISTANCE;
        else
            distance[i] = getDistanceSquared(pos, target);
    }
    sortDistances(distance, directions, DIRECTIONS_COUNT);
    return directions[0];
}

void sortDistances(int* distances, Direction* directions, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        bool isSwaped = false;
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (distances[j] > distances[j + 1] || 
                distances[j] == distances[j + 1] && (int)directions[j] > (int)directions[j + 1])
            {
                int temp = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = temp;

                temp = (int)directions[j];
                directions[j] = directions[j + 1];
                directions[j + 1] = (Direction)temp;

                isSwaped = true;
            }
        }
        if (!isSwaped)
            break;
    }
}

bool isValidPosition(const Position& pos, const Map& map, const Entity** ghosts, int ghostCount)
{
    return isValidCoordinate(pos.x, map.xSize) && isValidCoordinate(pos.y, map.ySize) 
        && !isWall(map.grid[pos.x][pos.y]) && !isThereOtherGhostOnPosition(pos, ghosts, ghostCount);
}

bool isThereOtherGhostOnPosition(const Position& pos, const Entity** ghosts, int ghostCount)
{
    for (int i = 0; i < ghostCount; i++)
    {
        if (areEqual(pos, ghosts[i]->position))
            return true;
    }
    return false;
}

void moveGhostToTarget(Entity& ghost, const Position& target, 
    const Map& map, const Entity** ghosts, int ghostCount)
{
    Direction dir = directionToShortestPathToTarget(ghost, target, map, ghosts, ghostCount);
    changeEntityDirection(ghost, dir);
    moveEntity(ghost);
}

void trackingBlinky(Entity& blinky, const Entity& pacMan, const Map& map, const Entity** ghosts, int ghostCount)
{
    moveGhostToTarget(blinky, pacMan.position, map, ghosts, ghostCount);
}

void trackingPinky(Entity& pinky, const Entity& pacMan, const Map& map, const Entity** ghosts, int ghostCount)
{
    Position target = pacMan.position;

    moveInDirection(target, pacMan.direction, PINKY_PREDICTION);
    if (pacMan.direction == PINKY_SPECIAL_DIRECTION)
        moveInDirection(target, PINKY_ADDITIONAL_DIRECTION, PINKY_PREDICTION);

    moveGhostToTarget(pinky, target, map, ghosts, ghostCount);
}

void trackingInky(Entity& inky, const Entity& pacMan, const Entity& blinky, 
    const Map& map, const Entity** ghosts, int ghostCount)
{
    Position center = pacMan.position;

    moveInDirection(center, pacMan.direction, INKY_PREDICTION);
    if (pacMan.direction == INKY_SPECIAL_DIRECTION)
        moveInDirection(center, INKY_ADDITIONAL_DIRECTION, INKY_PREDICTION);

    Position target = getMirroredPosition(center, blinky.position);

    moveGhostToTarget(inky, target, map, ghosts, ghostCount);
}

void trackingClyde(Entity& clyde, const Entity& pacMan, const Position& clydeFavouriteSpot, 
    const Map& map, const Entity** ghosts, int ghostCount)
{
    if (getDistance(clyde.position, pacMan.position) >= CLYDE_BEHAVIOR_DISTANCE)
        trackingBlinky(clyde, pacMan, map, ghosts, ghostCount);
    else
        moveGhostToTarget(clyde, clydeFavouriteSpot, map, ghosts, ghostCount);
}

void moveGhostRandomly(Entity& ghost, const Map& map, const Entity** ghosts, int ghostCount)
{
    Direction directions[DIRECTIONS_COUNT]{};
    int distance[DIRECTIONS_COUNT]{};
    for (int i = 0; i < DIRECTIONS_COUNT; i++)
    {
        directions[i] = (Direction)i;
        if (directions[i] == getOppositeDirection(ghost.direction))
        {
            distance[i] = BIG_DISTANCE - 1;
            continue;
        }

        Position pos = ghost.position;
        moveInDirection(pos, directions[i]);
        if (!isValidPosition(pos, map, ghosts, ghostCount))
            distance[i] = BIG_DISTANCE;
        else
            distance[i] = rand() % (BIG_DISTANCE - 2);
    }
    sortDistances(distance, directions, DIRECTIONS_COUNT);

    changeEntityDirection(ghost, directions[0]);
    moveEntity(ghost);
}
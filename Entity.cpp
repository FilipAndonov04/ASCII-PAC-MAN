#include "Entity.h"
#include <cmath>

Direction getOppositeDirection(Direction direction)
{
    switch (direction)
    {
    case Direction::Up:
        return Direction::Down;
    case Direction::Left:
        return Direction::Right;
    case Direction::Down:
        return Direction::Up;
    case Direction::Right:
        return Direction::Left;
    }
}

int getAbs(int num)
{
    return num > 0 ? num : -num;
}

int getDistanceSquared(const Position& p1, const Position& p2)
{
    int dx = getAbs(p1.x - p2.x);
    int dy = getAbs(p1.y - p2.y);
    return dx * dx + dy * dy;
}

double getDistance(const Position& p1, const Position& p2)
{
    return sqrt(getDistanceSquared(p1, p2));
}

Position getMirroredPosition(const Position& center, const Position& position)
{
    int x = 2 * center.x - position.x;
    int y = 2 * center.y - position.y;
    return { x, y };
}

void moveInDirection(Position& position, Direction direction)
{
    switch (direction)
    {
    case Direction::Up:
        position.x--;
        break;
    case Direction::Left:
        position.y--;
        break;
    case Direction::Down:
        position.x++;
        break;
    case Direction::Right:
        position.y++;
        break;
    }
}

void moveInDirection(Position& position, Direction direction, int count)
{
    for (int i = 0; i < count; i++)
    {
        moveInDirection(position, direction);
    }
}

bool areEqual(const Position& p1, const Position& p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

void changeEntityDirection(Entity& entity, Direction newDirection)
{
    entity.direction = newDirection;
}

void moveEntity(Entity& entity)
{
    moveInDirection(entity.position, entity.direction);
}

void turnEntityAround(Entity& entity)
{
    changeEntityDirection(entity, getOppositeDirection(entity.direction));
}

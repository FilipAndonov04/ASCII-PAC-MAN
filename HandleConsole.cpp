#include "HandleConsole.h"
#include <iostream>
#include <windows.h>

void updatePacManDirection(Entity& pacMan)
{
    if (GetAsyncKeyState(KEY_UP) & INPUT_MASK)
        changeEntityDirection(pacMan, Direction::Up);
    else if (GetAsyncKeyState(KEY_LEFT) & INPUT_MASK)
        changeEntityDirection(pacMan, Direction::Left);
    else if (GetAsyncKeyState(KEY_DOWN) & INPUT_MASK)
        changeEntityDirection(pacMan, Direction::Down);
    else if (GetAsyncKeyState(KEY_RIGHT) & INPUT_MASK)
        changeEntityDirection(pacMan, Direction::Right);
}

void setConsoleColour(int colourCode) 
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, colourCode);
}

char getColourFromChar(char ch)
{
    int colourCode;
    switch (ch)
    {
    case PAC_MAN_SYMBOL:
        colourCode = COLOUR_YELLOW;
        break;
    case BLINKY_SYMBOL:
        colourCode = COLOUR_RED;
        break;
    case PINKY_SYMBOL:
        colourCode = COLOUR_PINK;
        break;
    case INKY_SYMBOL:
        colourCode = COLOUR_BLUE;
        break;
    case CLYDE_SYMBOL:
        colourCode = COLOUR_GREEN;
        break;
    case WALL_SYMBOL:
        colourCode = COLOUR_LIGHT_GRAY;
        break;
    case SUPER_FOOD_SYMBOL:
        colourCode = COLOUR_ORANGE;
        break;
    default:
        colourCode = COLOUR_WHITE;
        break;
    }
    return colourCode;
}

void setCursorPosition(int row, int col)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { col, row };

    SetConsoleCursorPosition(hStdout, position);
}

void printEntity(const Entity& entity, char sign, bool isChaseMode)
{
    setCursorPosition(entity.position.x + OFFSET_X, entity.position.y);
    if (isChaseMode)
        setConsoleColour(getColourFromChar(sign));
    else
        setConsoleColour(GHOST_FRIGHTENED_COLOUR);
    std::cout << sign;
}

void resetCursorPosition()
{
    setCursorPosition(0, 0);
}

void prepareConsole(int row)
{
    setConsoleCursorVisibility(true);
    setConsoleColour(COLOUR_WHITE);
    setCursorPosition(row + OFFSET_X, 0);
}

void printGameWithoutEntities(const Map& map, int score, int maxScore)
{
    resetCursorPosition();
    setConsoleColour(COLOUR_WHITE);

    printScore(score, maxScore);
    printMap(map);
}

void printScore(int score, int maxScore)
{
    std::cout << "Score: " << score << "  Max Score: " << maxScore << '\n';
}

void printEntities(const Entity& pacMan, const Entity& blinky, const Entity& pinky,
    const Entity& inky, const Entity& clyde, bool isChaseMode)
{
    printEntity(pacMan, PAC_MAN_SYMBOL, true);
    printEntity(blinky, BLINKY_SYMBOL, isChaseMode);
    printEntity(pinky, PINKY_SYMBOL, isChaseMode);
    printEntity(inky, INKY_SYMBOL, isChaseMode);
    printEntity(clyde, CLYDE_SYMBOL, isChaseMode);
}

void printResultMessage(int result)
{
    if (result == 1)
        std::cout << "Congrats! You win!\n";
    else
        std::cout << "You lose!\n";
}

void printMap(const Map& map)
{
    for (int i = 0; i < map.xSize; i++)
    {
        for (int j = 0; j < map.ySize; j++)
        {
            setConsoleColour(getColourFromChar(map.grid[i][j]));
            std::cout << map.grid[i][j];
        }
        std::cout << '\n';
    }
}

void setConsoleCursorVisibility(bool isVisible)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = isVisible;
    SetConsoleCursorInfo(out, &cursorInfo);
}
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
* Starting point
*
*/

#include "Game.h"
#include <cstdlib>
#include <ctime>

constexpr char FILE_NAME[] = "map.txt";

int main()
{
	srand(time(0));

	Game game;
	MapErrorCode errorCode = loadGame(FILE_NAME, game);

	if (errorCode == MapErrorCode::Okay)
		runGame(game);
	else
		printMapErrorMessage(errorCode);
}
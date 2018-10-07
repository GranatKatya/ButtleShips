// BattleShips.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);


void GotoXY(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hStdOut, coord);

}

int main()
{

	Game game = Game();
	game.Run();

    return 0;
}


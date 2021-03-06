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
IntelligenceFactory * Rules() {

	int choose;
	GotoXY(0,10);
	cout << "Choose difficulty of game " << endl;
	cout << "1 - simple intelligence " << endl;
	cout << "2 - hard intelligence " << endl;
	cin >> choose;
	if (choose == 1) {

		return new SimpleIntelligenceFactory;
	}
	else if (choose == 2) {
		return new HardIntelligenceFactory;
	}
	//system("cls");
}

void RunGame() {
	//game.Run();
	//game.menu();
	
	//int difficulty = 2;
	IntelligenceFactory * factory = reinterpret_cast <IntelligenceFactory*>( new HardIntelligenceFactory());// по умолчанию
	ProgectInnterface   *	game = new ProxyForGame(factory);
	Menu menu;
	
	while (1) {
		//Game *game = Game::CreateGame();
		//	game.SetDifficulty(difficulty);

		menu.Print_Array();
		menu.GetClick();
		int selecteditem = menu.GetSelectedItem();
		if (selecteditem == 0) {
			game->Run(); //game.DeleteArrays();
			//difficulty = game.GetDifficulty();
			//difficulty++;
		}
		else if (selecteditem == 1) {/*rulse*/
			factory = Rules();
			game->SetIntelligenceFactory(factory);
			system("cls");
		}
		else { exit(0); }
		//if (difficulty > 5) { difficulty = 5; }
	}
}

int main()
{
	srand(time(NULL));
	RunGame();

	//Menu m = Menu();
	//m.

	//Game *game = Game::CreateGame();
	//Game *game1 = Game::CreateGame();

	//game->Run();

    return 0;
}


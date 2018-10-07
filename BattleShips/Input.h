#pragma once

#include "stdafx.h"




class INput {

	FieldInterface  *fieldUser = nullptr;

	FieldInterface  *fieldEnemy = nullptr;
	vector<COORD *> coord;
	Shot * shot = nullptr;

public:

	INput(FieldInterface  * fieldUser1, FieldInterface  *fieldEnemy1) { fieldUser = fieldUser1; fieldEnemy = fieldEnemy1; }

	void Clean() {
		GotoXY(0, 0);
		cout << "                                                      ";
		GotoXY(0, 1);
		cout << "                                                      ";
		GotoXY(0, 2);
		cout << "                                                      ";
		GotoXY(0, 3);
		cout << "                                                      ";
		GotoXY(0, 4);
		cout << "                                                      ";
		GotoXY(0, 5);
		cout << "                                                      ";
		GotoXY(0, 6);
		cout << "                                                      ";
		GotoXY(0, 7);
		cout << "                                                      ";
		GotoXY(0, 8);
		cout << "                                                      ";
		GotoXY(0, 9);
		cout << "                                                      ";
		GotoXY(0, 10);
		cout << "                                                      ";
		GotoXY(0, 11);
		cout << "                                                      ";
		GotoXY(0, 12);
		cout << "                                                      ";
		GotoXY(0, 13);
		cout << "                                                      ";
		GotoXY(0, 14);
		cout << "                                                      ";
		GotoXY(0, 15);
		cout << "                                                      ";
		GotoXY(0, 16);
		cout << "                                                      ";
		GotoXY(0, 17);
		cout << "                                                      ";
	}

	void CleanEror() {
		GotoXY(0, 20);
		cout << "                                                      ";
		GotoXY(0, 21);
		cout << "                                                      ";
	}
	void GetCoordFormUser(int size) {
		

		//Goto();--------------------------!!!!!!!!!!!!!!!!!!!!
		
		Clean();

		

		char chx;
		int y;
		COORD *c = nullptr;

		for (size_t i = 0; i < size; i++)
		{
			GotoXY(0, 0);
			cout << "                                                      ";
			GotoXY(0, 1);
			cout << "                                                      ";
			GotoXY(0, 2);
			cout << "                                                      ";
			GotoXY(0, 3);
			cout << "                                                      ";
			GotoXY(0, 0);

			cout << "Enter X for " << i << "segment of " << size << " - deck ship" << endl;
			cin >> chx;

			int x = (int)chx - 97;
			if (x < 0 || x > 9) {
				GotoXY(0, 20);
				cout << "Please enter letter between a-j " << endl;
			//	GotoXY();
				i--;
				continue;
			}
			cout << "Enter Y for " << i << "segment of " << size << " - deck ship" << endl;
			cin >> y;
			if (y < 1 || y > 10) {
				GotoXY(0, 20);
				cout << "Please enter digit between 1-10" << endl;
				i--;
				continue;
			}

			c = new COORD();

			c->X = x;
			c->Y = y-1;
			coord.push_back(c);
		}
	

	}

	bool IsCoordsLine() {
		bool vertical_line = true;
		bool horizontal_line = true;

		for (size_t i = 1; i < coord.size(); i++)
		{
			if (coord[0]->X != coord[i]->X || (coord[i - 1]->Y != coord[i]->Y +1 && coord[i - 1]->Y != coord[i]->Y -1)) {
				vertical_line = false;
			}
			if (coord[0]->Y != coord[i]->Y || (coord[i - 1]->X != coord[i]->X + 1 && coord[i - 1]->X != coord[i]->X - 1)) {
				horizontal_line = false;
			}
		}
		if (vertical_line || horizontal_line) {
			return true;
		}
		else
		{
			return false;
		}

	}

	void SetUpFleet() {//в начале  Game

		CleanEror();
		GetValidatedCoords(4);
		fieldUser->CreateShip(coord);
		cout << "Ship created" << endl;
		fieldUser->PrintShips();
		

		CleanEror();
		GetValidatedCoords(3);
		fieldUser->CreateShip(coord);
		cout << "Ship created" << endl;
		fieldUser->PrintShips();
		CleanEror();
		GetValidatedCoords(3);
		fieldUser->CreateShip(coord);
		cout << "Ship created" << endl;
		fieldUser->PrintShips();

		CleanEror();
		GetValidatedCoords(2);
		fieldUser->CreateShip(coord);
		cout << "Ship created" << endl;
		fieldUser->PrintShips();
		CleanEror();
		GetValidatedCoords(2);
		fieldUser->CreateShip(coord);
		cout << "Ship created" << endl;
		fieldUser->PrintShips();
		CleanEror();
		GetValidatedCoords(2);
		fieldUser->CreateShip(coord);
		cout << "Ship created" << endl;
		fieldUser->PrintShips();

		CleanEror();
		GetValidatedCoords(1);
		fieldUser->CreateShip(coord);
		cout << "Ship created" << endl;
		fieldUser->PrintShips();
		CleanEror();
		GetValidatedCoords(1);
		fieldUser->CreateShip(coord);
		cout << "Ship created" << endl;
		fieldUser->PrintShips();
		CleanEror();
		GetValidatedCoords(1);
		fieldUser->CreateShip(coord);
		cout << "Ship created" << endl;
		fieldUser->PrintShips();
		CleanEror();
		GetValidatedCoords(1);
		fieldUser->CreateShip(coord);
		cout << "Ship created" << endl;
		fieldUser->PrintShips();

		CleanEror();
		GetValidatedCoords(1);
		fieldUser->CreateMine(coord);
		cout << "Ship created" << endl;
		fieldUser->PrintShips();
		CleanEror();
		Clean();

	}

	void CleanCoordArray() {
		coord.clear();
	}

	void GetValidatedCoords(int size) {
		bool coords_valid = true;
		while (1) {
			coords_valid = true;

			CleanCoordArray();

			// get coords size from user
			GetCoordFormUser(size);



			if (!IsCoordsLine()) {
				// Print error
				GotoXY(0, 20);
				cout << "                               ";
				GotoXY(0, 20);
				cout << "Ship coords shoud form a row" << endl;

				continue;	
			}
			for (size_t i = 0; i < coord.size(); i++)
			{
				if (!fieldUser->AreSurraundionCellsEmpty(coord[i]->X, coord[i]->Y)) {
					// Print another error
					GotoXY(0, 20);
					cout << "                                              " << endl;
					GotoXY(0,20);
					cout << "Ship shoud not be adjacent to enother object" << endl;
					coords_valid = false;
					break;

				}
			}
			if (!coords_valid) { continue; }
			break;
		}

	
	}	

	void RequestShot() {

		while (1) {

		CleanCoordArray();
		GetCoordFormUser(1);
		delete shot;
		shot = nullptr;

		//IsHitCell	

			if (fieldEnemy->GetCellByCoord(coord[0]->X, coord[0]->Y)->GetIsShut()) {
				GotoXY(0,20);
				cout << "You cant shot in a cell that was already hit" << endl;
				continue;
			}
			

			shot = new Shot;
			shot->SetX(coord[0]->X);
			shot->SetY(coord[0]->Y);

			break;
		}
	}
	Shot &GetShot() { return *shot; }

};
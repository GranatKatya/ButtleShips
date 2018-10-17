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
		cout << "                                      ";
		GotoXY(0, 1);
		cout << "                                      ";
		GotoXY(0, 2);
		cout << "                                      ";
		GotoXY(0, 3);
		cout << "                                      ";
		GotoXY(0, 4);
		cout << "                                      ";
		GotoXY(0, 5);
		cout << "                                      ";
		GotoXY(0, 6);
		cout << "                                      ";
		GotoXY(0, 7);
		cout << "                                      ";
		GotoXY(0, 8);
		cout << "                                      ";
		GotoXY(0, 9);
		cout << "                                      ";
		GotoXY(0, 10);
		cout << "                                      ";
		GotoXY(0, 11);
		cout << "                                      ";
		GotoXY(0, 12);
		cout << "                                      ";
		GotoXY(0, 13);
		cout << "                                      ";
		GotoXY(0, 14);
		cout << "                                      ";
		GotoXY(0, 15);
		cout << "                                      ";
		GotoXY(0, 16);
		cout << "                                      ";
		GotoXY(0, 17);
		cout << "                                      ";

	
	}

	void CleanEror() {
		GotoXY(0, 20);
		cout << "                                               ";
		GotoXY(0, 21);
		cout << "                                               ";
	}
	void GetCoordFormUser(int size, int input) {		
		
		Clean();

		char chx;
		char y;
		COORD *c = nullptr;
		int x;

		for (size_t i = 0; i < size; i++)
		{
			Clean();
			
				GotoXY(0, 0);

				if (input == 1) {
					cout << "Enter X for " << i << " segment of " << size << " - deck ship" << endl;

					cin >> chx;

				}
				else if (input == 2) {
					cout << "Choose X for ship to exploude" << endl;
					cin >> chx;
				}
				else {
					cout << "Enter X for move" << endl;
					cin >> chx;
				}


				 x = (int)chx - 97;
				if (x < 0 || x > 9) {
					PrintStatus("Please enter letter between a-j ");
					//	cout << "Please enter letter between a-j " << endl;
					i--;
					continue;
				}

				/*while (1)
				{*/
				if (input == 1) {
					cout << "Enter Y for " << i << "segment of " << size << " - deck ship" << endl;
					/*try {
						cin.exceptions( ios::fail);*/
					cin >> y;

					/*}
					catch (exception  ex) {
						Sleep(100);
					}*/
				}
				else if (input == 2) {

					cout << "Choose Y for ship to exploude" << endl;

					cin >> y;

				}
				else {
					cout << "Enter Y for move" << endl;
					cin >> y;

					//try {
					//	if (cin.fail()) {
					//		throw 4;
					//	}
					//}
					//catch (int i) {
					//	std::cout << "Invalid input" << std::endl;
					//	//cin.clear();
					//	Sleep(1000);
					//	exit(0);
					//	//break;
					//}break;

				}
				int y1 = y -'0' ;

				if (y1 < 0|| y1 > 9) {
					//Clean();
					PrintStatus("Please enter digit between 1-10");
					i--;
					continue;
				}
		//	}

				y1 += 1;

			//int32_t example;
			//while (1) {
			//	std::cin >> example;

			//	try {
			//		if (cin.fail()) {
			//			throw 4;
			//		}
			//	}
			//	catch (int i) {
			//		std::cout << "Invalid input" << std::endl;
			//		cin.clear();
			//		break;
			//	}
			//}

			c = new COORD();

			c->X = x;
			c->Y = y1-1;
			coord.push_back(c);
		}
	

	}

	void PrintStatus(const char* str) {
		GotoXY(0, 20);
		cout << "                                                ";
		GotoXY(0, 21);
		cout << "                                                ";

		Clean();
		GotoXY(0,20);
		cout << str;
	}


	void RequestShipToExploude() {
		while (1) {
			coord.clear();

			GetCoordFormUser(1, 2);//"Choose Y for ship to exploude" 
			
			if (fieldUser->GetCellByCoord(coord[0]->X, coord[0]->Y)->GetGameObject() == nullptr) {
				PrintStatus("Please specify correct coords of your ship");
				//cout << "Please specify correct coords of your ship" << endl;
				continue;
			}
			//else if(fieldUser->GetCellByCoord(coord[0]->X, coord[0]->Y)->GetGameObject())
			if (fieldUser->GetCellByCoord(coord[0]->X, coord[0]->Y)->GetGameObject()->ObjectType() == 2) {
				PrintStatus("Please specify correct coords of your ship (not bomb)");
			//	cout << "Please specify correct coords of your ship (not bomb)" << endl;
				continue;
			}
			if (fieldUser->GetCellByCoord(coord[0]->X, coord[0]->Y)->GetIsShut()) {
				PrintStatus("Please specify coord that has not been shut");
			//	cout << "Please specify coord that has not been shut" << endl;
				continue;
			}
			else {

				delete shot;
				shot = nullptr;

				shot = new Shot;
				shot->SetX(coord[0]->X);
				shot->SetY(coord[0]->Y);

				break;
			}

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


	 void GetValidateCoordsTest(int size) { // поставит корабли
		vector<Cell*> arr = fieldUser->GetEmptyCells();
		//	srand(time(NULL));
		int x;
		int direction;


		while (1) {
			CleanCoordArray();
			x = rand() % arr.size();
			direction = rand() % 4;

			if (!fieldUser->AreSurraundionCellsEmpty(arr[x]->GetX(), arr[x]->GetY())) {
				continue;
			}

			//COORD *coord = new COORD;
			coord.push_back(new COORD());
			coord[coord.size() - 1]->X = arr[x]->GetX();
			coord[coord.size() - 1]->Y = arr[x]->GetY();

			Cell * current = arr[x];
			bool continue_flag = false;

			for (size_t i = 1; i < size; i++)
			{
				if (direction == 0) {//right

					if (current->GetR() == nullptr || !fieldUser->AreSurraundionCellsEmpty(current->GetR()->GetX(), current->GetR()->GetY())) { // if right cell does not satisfy conditions try another one
						continue_flag = true;
						break;
					}
					current = current->GetR();

				}
				else if (direction == 1) {//down
					if (current->GetD() == nullptr || !fieldUser->AreSurraundionCellsEmpty(current->GetD()->GetX(), current->GetD()->GetY())) { // if right cell does not satisfy conditions try another one
						continue_flag = true;
						break;
					}
					current = current->GetD();
				}
				else if (direction == 2) {//left
					if (current->GetL() == nullptr || !fieldUser->AreSurraundionCellsEmpty(current->GetL()->GetX(), current->GetL()->GetY())) { // if right cell does not satisfy conditions try another one
						continue_flag = true;
						break;
					}
					current = current->GetL();
				}
				else {//up
					if (current->GetU() == nullptr || !fieldUser->AreSurraundionCellsEmpty(current->GetU()->GetX(), current->GetU()->GetY())) { // if right cell does not satisfy conditions try another one
						continue_flag = true;
						break;
					}
					current = current->GetU();
				}

				//_ship_coords.push_back(COORD(current->GetX(), current->GetY()));
				coord.push_back(new COORD());
				coord[coord.size() - 1]->X = current->GetX();
				coord[coord.size() - 1]->Y = current->GetY();

			}
			if (continue_flag) { continue; }
			break;
		}
	}



	void SetUpFleet() {//в начале  Game

		CleanEror();
		//PrintStatus("");
		GetValidatedCoords(4);
		fieldUser->CreateShip(coord);
		//PrintStatus("Ship created");
		fieldUser->PrintShips();
		

		CleanEror();
		//PrintStatus("");
		GetValidatedCoords(3);
		fieldUser->CreateShip(coord);
	//	PrintStatus("Ship created");
		fieldUser->PrintShips();
		CleanEror();
		//PrintStatus("");
		GetValidatedCoords(3);
		fieldUser->CreateShip(coord);
	//	PrintStatus("Ship created");
		fieldUser->PrintShips();

		CleanEror();
		//PrintStatus("");
		GetValidatedCoords(2);
		fieldUser->CreateShip(coord);
		//PrintStatus("Ship created");
		fieldUser->PrintShips();
		CleanEror();
		//PrintStatus("");
		GetValidatedCoords(2);
		fieldUser->CreateShip(coord);
		//PrintStatus("Ship created");	
		fieldUser->PrintShips();
		CleanEror();
		//PrintStatus("");
		GetValidatedCoords(2);
		fieldUser->CreateShip(coord);
		//PrintStatus("Ship created");	
		fieldUser->PrintShips();

//		PrintStatus("");
		CleanEror();
		GetValidatedCoords(1);
		fieldUser->CreateShip(coord);
	//	PrintStatus("Ship created");
		fieldUser->PrintShips();
		CleanEror();
		//PrintStatus("");
		GetValidatedCoords(1);
		fieldUser->CreateShip(coord);
		//PrintStatus("Ship created");
		fieldUser->PrintShips();
		CleanEror();
		//PrintStatus("");
		GetValidatedCoords(1);
		fieldUser->CreateShip(coord);
		//PrintStatus("Ship created");
		fieldUser->PrintShips();
		CleanEror();
		//PrintStatus("");
		GetValidatedCoords(1);
		fieldUser->CreateShip(coord);
		//PrintStatus("Ship created");
		fieldUser->PrintShips();

		CleanEror();
		//PrintStatus("");
		GetValidatedCoords(1);
		fieldUser->CreateMine(coord);
		//PrintStatus("Ship created");
		fieldUser->PrintShips();
		CleanEror();
		//PrintStatus("");
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
			GetCoordFormUser(size,1);



			if (!IsCoordsLine()) {


				PrintStatus("Ship coords shoud form a row");
				
				continue;	
			}
			for (size_t i = 0; i < coord.size(); i++)
			{
				if (!fieldUser->AreSurraundionCellsEmpty(coord[i]->X, coord[i]->Y)) {
					// Print another error
					PrintStatus("Ship shoud not be adjacent to enother object");
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
		GetCoordFormUser(1,3);
		delete shot;
		shot = nullptr;

		//IsHitCell	

			if (fieldEnemy->GetCellByCoord(coord[0]->X, coord[0]->Y)->GetIsShut()) {
				PrintStatus("You cant shot in a cell that was already hit");
				//GotoXY(0,20);
				//cout << "You cant shot in a cell that was already hit" << endl;
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
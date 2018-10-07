#pragma once

#include "stdafx.h"

class InterfaceIntelligence {

protected:
	FieldInterface * _fieldEnemy = nullptr;
	FieldInterface * _fieldInterface = nullptr;
	Shot * shot = nullptr; // -???????????????????????????????????????????????????????????
	vector<COORD*> _ship_coords;

public:

	//InterfaceIntelligence(FieldInterface  * fieldUser1, FieldInterface  *fieldEnemy1) { _fieldInterface = fieldUser1; _fieldEnemy = fieldEnemy1; }

	virtual void RandomTurn() = 0;
	virtual void FinisherTurn() = 0;
	virtual void SetUpFleet() {

		GetValidateCoords(4);
		_fieldEnemy->CreateShip(_ship_coords);

		GetValidateCoords(3);
		_fieldEnemy->CreateShip(_ship_coords);
		GetValidateCoords(3);
		_fieldEnemy->CreateShip(_ship_coords);

		GetValidateCoords(2);
		_fieldEnemy->CreateShip(_ship_coords);
		GetValidateCoords(2);
		_fieldEnemy->CreateShip(_ship_coords);
		GetValidateCoords(2);
		_fieldEnemy->CreateShip(_ship_coords);

		GetValidateCoords(1);
		_fieldEnemy->CreateShip(_ship_coords);
		GetValidateCoords(1);
		_fieldEnemy->CreateShip(_ship_coords);
		GetValidateCoords(1);
		_fieldEnemy->CreateShip(_ship_coords);
		GetValidateCoords(1);
		_fieldEnemy->CreateShip(_ship_coords);

		GetValidateCoords(1);
		_fieldEnemy->CreateMine(_ship_coords);

	}


	void CleanCoordArray() {
		for (size_t i = 0; i <_ship_coords.size(); i++)
		{
			_ship_coords.pop_back();
		}
	}
	virtual void GetValidateCoords(int size) { // поставит корабли
		vector<Cell*> arr = _fieldInterface->GetEmptyCells();
		srand(time(NULL));
		int x;
		int direction;


		while (1) {
			CleanCoordArray();
			x = rand() % arr.size();
			direction = rand() % 4;

			if (!_fieldInterface->AreSurraundionCellsEmpty(arr[x]->GetX(), arr[x]->GetY())) {
				continue;
			}

			//COORD *coord = new COORD;
			_ship_coords.push_back(new COORD());
			_ship_coords[_ship_coords.size()-1]->X = arr[x]->GetX();
			_ship_coords[_ship_coords.size()-1]->Y = arr[x]->GetY();

			Cell * current = arr[x];
			bool continue_flag = false;

			for (size_t i = 1; i < size; i++)
			{
				if (direction == 0) {//right
					
					if (current->GetR() == nullptr || !_fieldInterface->AreSurraundionCellsEmpty(current->GetR()->GetX(), current->GetR()->GetY())) { // if right cell does not satisfy conditions try another one
						continue_flag = true;
						break;
					}
					current = current->GetR();
					
				}
				else if (direction == 1 ) {//down
					if (current->GetD() == nullptr || !_fieldInterface->AreSurraundionCellsEmpty(current->GetD()->GetX(), current->GetD()->GetY())) { // if right cell does not satisfy conditions try another one
						continue_flag = true;
						break;
					}
					current = current->GetD();
				}
				else if (direction == 2) {//left
					if (current->GetL() == nullptr || !_fieldInterface->AreSurraundionCellsEmpty(current->GetL()->GetX(), current->GetL()->GetY())) { // if right cell does not satisfy conditions try another one
						continue_flag = true;
						break;
					}
					current = current->GetL();
				}
				else  {//up
					if (current->GetU() == nullptr || !_fieldInterface->AreSurraundionCellsEmpty(current->GetU()->GetX(), current->GetU()->GetY())) { // if right cell does not satisfy conditions try another one
						continue_flag = true;
						break;
					}
					current = current->GetU();
				}

				//_ship_coords.push_back(COORD(current->GetX(), current->GetY()));
				_ship_coords.push_back(new COORD());
				_ship_coords[_ship_coords.size() - 1]->X = current->GetX();
				_ship_coords[_ship_coords.size() - 1]->Y = current->GetY();

			}
			if (continue_flag) { continue; }
			break;
		}
	}

	Shot &GetShot() { return *shot; }


};

class SimpleIntelligence  : public InterfaceIntelligence {

public:

	SimpleIntelligence(FieldInterface & field, FieldInterface & field2) {
		_fieldEnemy = &field;
		_fieldInterface = &field2;
	}
	virtual void RandomTurn() {

		vector<Cell*> arr = _fieldInterface->GetUnshutCells();

		srand(time(NULL));
		int x = rand() % arr.size();

		shot = new Shot;
		shot->SetX(arr[x]->GetX());
		shot->SetY(arr[x]->GetY());
	}
	virtual void FinisherTurn() {
		RandomTurn();
	}
	

};

class HardIntelligence : public InterfaceIntelligence {

public:
	HardIntelligence(FieldInterface & field, FieldInterface & field2) {
		_fieldEnemy = &field;
		_fieldInterface = &field2;
	}
	virtual void RandomTurn() {}
	virtual void FinisherTurn() {}


};


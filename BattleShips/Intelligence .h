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

	virtual void RandomTurn() {
		vector<Cell*> arr = _fieldInterface->GetUnshutCells();

		int x;

		for (;;) {
			x = rand() % arr.size();
			if (!IsAdjacentToDestroyedShip(arr[x])) {
				break;
			}
		
		}
			shot = new Shot;
			shot->SetX(arr[x]->GetX());
			shot->SetY(arr[x]->GetY());
		
	}
	//virtual void FinisherTurn() = 0;//

	virtual void SetUpFleet() {

		GetValidateCoords(4);
		_fieldEnemy->CreateShip(_ship_coords);
		//_fieldEnemy->PrintShips();


		GetValidateCoords(3);
		_fieldEnemy->CreateShip(_ship_coords);
		//_fieldEnemy->PrintShips();
		GetValidateCoords(3);
		_fieldEnemy->CreateShip(_ship_coords);
		//_fieldEnemy->PrintShips();

		GetValidateCoords(2);
		_fieldEnemy->CreateShip(_ship_coords);
		//_fieldEnemy->PrintShips();
		GetValidateCoords(2);
		_fieldEnemy->CreateShip(_ship_coords);
		//_fieldEnemy->PrintShips();
		GetValidateCoords(2);
		_fieldEnemy->CreateShip(_ship_coords);
		//_fieldEnemy->PrintShips();

		GetValidateCoords(1);
		_fieldEnemy->CreateShip(_ship_coords);
		//_fieldEnemy->PrintShips();
		GetValidateCoords(1);
		_fieldEnemy->CreateShip(_ship_coords);
		//_fieldEnemy->PrintShips();
		GetValidateCoords(1);
		_fieldEnemy->CreateShip(_ship_coords);
		//_fieldEnemy->PrintShips();
		GetValidateCoords(1);
		_fieldEnemy->CreateShip(_ship_coords);
		//_fieldEnemy->PrintShips();

		GetValidateCoords(1);
		_fieldEnemy->CreateMine(_ship_coords);
		//_fieldEnemy->PrintShips();

	}


	void CleanCoordArray() {

		_ship_coords.clear();
	}
	virtual void GetValidateCoords(int size) { // поставит корабли
		vector<Cell*> arr = _fieldEnemy->GetEmptyCells();
	//	srand(time(NULL));
		int x;
		int direction;


		while (1) {
			CleanCoordArray();
			x = rand() % arr.size();
			direction = rand() % 4;

			if (!_fieldEnemy->AreSurraundionCellsEmpty(arr[x]->GetX(), arr[x]->GetY())) {
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
					
					if (current->GetR() == nullptr || !_fieldEnemy->AreSurraundionCellsEmpty(current->GetR()->GetX(), current->GetR()->GetY())) { // if right cell does not satisfy conditions try another one
						continue_flag = true;
						break;
					}
					current = current->GetR();
					
				}
				else if (direction == 1 ) {//down
					if (current->GetD() == nullptr || !_fieldEnemy->AreSurraundionCellsEmpty(current->GetD()->GetX(), current->GetD()->GetY())) { // if right cell does not satisfy conditions try another one
						continue_flag = true;
						break;
					}
					current = current->GetD();
				}
				else if (direction == 2) {//left
					if (current->GetL() == nullptr || !_fieldEnemy->AreSurraundionCellsEmpty(current->GetL()->GetX(), current->GetL()->GetY())) { // if right cell does not satisfy conditions try another one
						continue_flag = true;
						break;
					}
					current = current->GetL();
				}
				else  {//up
					if (current->GetU() == nullptr || !_fieldEnemy->AreSurraundionCellsEmpty(current->GetU()->GetX(), current->GetU()->GetY())) { // if right cell does not satisfy conditions try another one
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

	virtual void RequestShipToExploude() {
		vector<Cell*> unshut_cells = _fieldEnemy->GetUnshutsCellsFromShips();
		int random = rand() % unshut_cells.size();

		//	coord.clear();
		delete shot;
		shot = nullptr;

		shot = new Shot;
		shot->SetX(unshut_cells[random]->GetX());
		shot->SetY(unshut_cells[random]->GetY());

	}

	virtual  bool IsAdjacentToDestroyedShip(Cell* cell) {
		vector<Cell*> surroundingcells = cell->GetSurroundingCells();

		for (size_t i = 0; i < surroundingcells.size(); i++)
		{
			if(surroundingcells[i]->GetGameObject() != nullptr){
				if (surroundingcells[i]->GetGameObject()->IsDead()) {
					return true;
				}
			}
		}
		return false;
	}
};

class SimpleIntelligence  : public InterfaceIntelligence {

public:
	SimpleIntelligence() {}
	SimpleIntelligence(FieldInterface & field, FieldInterface & field2) {
		_fieldEnemy = &field;
		_fieldInterface = &field2;
	}
	


};

class HardIntelligence : public InterfaceIntelligence {

public:
	HardIntelligence() {}
	HardIntelligence(FieldInterface & field, FieldInterface & field2) {
		_fieldEnemy = &field;
		_fieldInterface = &field2;
	}
	virtual void RandomTurn() {
		vector<Cell*> wonded_cells = _fieldInterface->GetWoundedClls();
		int direction = 0;
		int index=-1;

		if (wonded_cells.size() == 0) {
			InterfaceIntelligence::RandomTurn();
			return;
		}
		else {
			for (size_t i = 0; i < wonded_cells.size(); i++)
			{
				if (wonded_cells[i]->GetR() != nullptr) {
					if (wonded_cells[i]->GetR()->GetGameObject() != nullptr &&
						wonded_cells[i]->GetR()->GetIsShut()) {
						direction = 1;
						index = i;
						break;
					}
				}
				if (wonded_cells[i]->GetD() != nullptr) {
					if (wonded_cells[i]->GetD()->GetGameObject() != nullptr &&
						wonded_cells[i]->GetD()->GetIsShut()) {
						direction = 2;
						index = i;
						break;
					}
				}
			}
		}

		int random = rand() % 4;
		delete shot;
		shot = nullptr;
		shot = new Shot;
		Cell *current_cell = nullptr;
		if(index==-1){
			index = rand() % wonded_cells.size();
			for (;;) {

				if (random == 0)
				{
					if (wonded_cells[index]->GetR() != nullptr && !wonded_cells[index]->GetR()->GetIsShut() ) {
						shot->SetX(wonded_cells[index]->GetR()->GetX());
						shot->SetY(wonded_cells[index]->GetR()->GetY());
						return;
					}else{
						random = (random + 1) % 4; 
						continue;
					}
				}
				if (random == 1)
				{
					if (wonded_cells[index]->GetD() != nullptr && !wonded_cells[index]->GetD()->GetIsShut()) {
						shot->SetX(wonded_cells[index]->GetD()->GetX());
						shot->SetY(wonded_cells[index]->GetD()->GetY());
						return;
					}
					else {
						random = (random + 1) % 4;
						continue;
					}
				}
				if (random == 2)
				{
					if (wonded_cells[index]->GetL() != nullptr && !wonded_cells[index]->GetL()->GetIsShut()) {
						shot->SetX(wonded_cells[index]->GetL()->GetX());
						shot->SetY(wonded_cells[index]->GetL()->GetY());
						return;
					}
					else {
						random = (random + 1) % 4;
						continue;
					}
				}
				if (random == 3)
				{
					if (wonded_cells[index]->GetU() != nullptr && !wonded_cells[index]->GetU()->GetIsShut()) {
						shot->SetX(wonded_cells[index]->GetU()->GetX());
						shot->SetY(wonded_cells[index]->GetU()->GetY());
						return;
					}
					else {
						random = (random + 1) % 4; // this returns 4 withot parenthes!
						continue;
					}
				}
			
			}
		}
		else {
			random = random % 2;
			current_cell = wonded_cells[index];
			for (;;)
			{
				if (direction == 1) {
					if (random)
					{
						if (current_cell->GetR() != nullptr && !(current_cell->GetR()->GetIsShut() && current_cell->GetR()->GetGameObject() == nullptr)) {
							if (current_cell->GetR()->GetIsShut()) {
								current_cell = current_cell->GetR();
							}
							else {
								shot->SetX(current_cell->GetR()->GetX());
								shot->SetY(current_cell->GetR()->GetY());
								return;
							}
						}
						else {
							random = !random;
						}
					}
					else {
						if (current_cell->GetL() != nullptr && !(current_cell->GetL()->GetIsShut() && current_cell->GetL()->GetGameObject() == nullptr)) {
							if (current_cell->GetL()->GetIsShut()) {
								current_cell = current_cell->GetL();
							}
							else {
								shot->SetX(current_cell->GetL()->GetX());
								shot->SetY(current_cell->GetL()->GetY());
								return;
							}
						}
						else {
							random = !random;
						}
					} // if (random)

				}
				else {
					if (random)
					{
						if (current_cell->GetU() != nullptr && !(current_cell->GetU()->GetIsShut() && current_cell->GetU()->GetGameObject() == nullptr)) {
							if (current_cell->GetU()->GetIsShut()) {
								current_cell = current_cell->GetU();
							}
							else {
								shot->SetX(current_cell->GetU()->GetX());
								shot->SetY(current_cell->GetU()->GetY());
								return;
							}
						}
						else {
							random = !random;
						}
					}
					else {
						if (current_cell->GetD() != nullptr && !(current_cell->GetD()->GetIsShut() && current_cell->GetD()->GetGameObject() == nullptr)) {
							if (current_cell->GetD()->GetIsShut()) {
								current_cell = current_cell->GetD();
							}
							else {
								shot->SetX(current_cell->GetD()->GetX());
								shot->SetY(current_cell->GetD()->GetY());
								return;
							}
						}
						else {
							random = !random;
						}
					}
				}// if (direction)
			} // for (;;)
		}//if (index)
	}
	
	
	


};




class IntelligenceFactory {

public:
	virtual InterfaceIntelligence * createIntelligence(FieldInterface & field, FieldInterface & field2) = 0;
};

class SimpleIntelligenceFactory : public IntelligenceFactory {

public:
	virtual InterfaceIntelligence * createIntelligence(FieldInterface & field, FieldInterface & field2) {
		return new SimpleIntelligence(field, field2);
	}

};

class HardIntelligenceFactory : public IntelligenceFactory {

public:
	virtual InterfaceIntelligence * createIntelligence(FieldInterface & field, FieldInterface & field2) {
		return new HardIntelligence(field, field2);
	}

};
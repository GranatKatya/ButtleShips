#pragma once
#include "stdafx.h"



class FieldInterface {
protected:
	vector<Cell*> _arr_of_cells;
	vector<GameObject*> _arr_of_ships;
	vector<Cell*>_arr_of_markup;
	int _x_shift;
	int _y_shift;

public:
	/*FieldInterface(int x_shift, int y_shift) {
		_x_shift = x_shift;
		_y_shift = y_shift;
	}*/
	
	virtual vector<Cell*> GetUnshutCells();
	virtual  vector<Cell*> GetEmptyCells();

	virtual void InitializeField();
	virtual void PrintField() = 0;
	virtual void CreateShip(vector<COORD*> coord);

	virtual void CreateMine(vector<COORD*> coord);

	Cell* GetCellByCoord(int x, int y);
	bool IsEmpty(int x, int y);

	bool AreSurraundionCellsEmpty(int x, int y);

	void ProcessShot(Shot &shot);

	void PrintShips() {
		for (size_t i = 0; i < _arr_of_ships.size(); i++)
		{
			_arr_of_ships[i]->PrintGameObject();//initialized
		}
	}

	vector<Cell*>  GetUnshutsCellsFromShips() {
		vector<Cell*> unshut_cells;
		//int random = rand() % _arr_of_ships.size();
		for (size_t j = 0; j < _arr_of_ships.size(); j++)
		{
			for (size_t i = 0; i < _arr_of_ships[j]->GetArrayOfCells()->size(); i++)
			{
				if ((*_arr_of_ships[j]->GetArrayOfCells())[i]->GetIsShut() == false &&
					(*_arr_of_ships[j]->GetArrayOfCells())[i]->GetGameObject()->ObjectType() != 2) {
					unshut_cells.push_back((*_arr_of_ships[j]->GetArrayOfCells())[i]);
				}
			}
		}
		return unshut_cells;
	}

	vector<Cell*>  GetShutsCellsFromShips() {
		vector<Cell*> unshut_cells;
		//int random = rand() % _arr_of_ships.size();
		for (size_t j = 0; j < _arr_of_ships.size(); j++)
		{
			for (size_t i = 0; i < _arr_of_ships[j]->GetArrayOfCells()->size(); i++)
			{
				if ((*_arr_of_ships[j]->GetArrayOfCells())[i]->GetIsShut() == true &&
					(*_arr_of_ships[j]->GetArrayOfCells())[i]->GetGameObject()->ObjectType() != 2) {
					unshut_cells.push_back((*_arr_of_ships[j]->GetArrayOfCells())[i]);
				}
			}
		}
		return unshut_cells;
	}

	vector<Cell*> GetWoundedClls() {	
		vector<Cell*> unshut_cells = GetShutsCellsFromShips();
		vector<Cell*> wounded_cells;
		for (size_t j = 0; j < unshut_cells.size(); j++)
		{

			if (!unshut_cells[j]->GetGameObject()->IsDead()) {
				wounded_cells.push_back(unshut_cells[j]);
			}
		}
		return wounded_cells;
	}

};



class UserField  : public FieldInterface {
	
public: 
	UserField(int x_shift, int y_shift);
	virtual void PrintField();
};


class EnemyField : public FieldInterface{

public:
	EnemyField(int x_shift, int y_shift);
	virtual void PrintField();
};

#pragma once
#include "stdafx.h"



class FieldInterface {
protected:
	vector<Cell*> _arr_of_cells;
	vector<GameObject*> _arr_of_ships;
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

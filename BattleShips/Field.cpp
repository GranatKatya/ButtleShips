
#include "stdafx.h"





	 vector<Cell*> FieldInterface::GetUnshutCells() {
		vector<Cell*> unshut_cells;
		for (size_t i = 0; i < _arr_of_cells.size(); i++)
		{
			if (!_arr_of_cells[i]->GetIsShut())
			{
				unshut_cells.push_back(_arr_of_cells[i]);
			}
		}
		return unshut_cells;
	}
	  vector<Cell*> FieldInterface::GetEmptyCells() {
		vector<Cell*> unshut_cells;
		for (size_t i = 0; i < _arr_of_cells.size(); i++)
		{
			if (_arr_of_cells[i]->GetGameObject() == nullptr)
			{
				unshut_cells.push_back(_arr_of_cells[i]);
			}
		}
		return unshut_cells;

	}

	 void FieldInterface::InitializeField() {
		for (size_t i = 0; i < 10; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				Cell *ptr_cell = new Cell(i, j, _x_shift, _y_shift);
				_arr_of_cells.push_back(ptr_cell);

				if (i != 0) {//столбцы
					_arr_of_cells[_arr_of_cells.size() - 1]->SetL(&(*_arr_of_cells[_arr_of_cells.size() - 11]));
					_arr_of_cells[_arr_of_cells.size() - 11]->SetR(&(*_arr_of_cells[_arr_of_cells.size() - 1]));
				}
				if (j != 0) {
					_arr_of_cells[_arr_of_cells.size() - 1]->SetU(&(*_arr_of_cells[_arr_of_cells.size() - 2]));
					_arr_of_cells[_arr_of_cells.size() - 2]->SetD(&(*_arr_of_cells[_arr_of_cells.size() - 1]));
				}
			}
		}
	}
	
	 void FieldInterface::CreateShip(vector<COORD*> coord) {

		Ship *ship = new Ship;
		for (size_t i = 0; i < coord.size(); i++)
		{
			ship->GetArrayOfCells()->push_back(GetCellByCoord(coord[i]->X, coord[i]->Y));
			GetCellByCoord(coord[i]->X, coord[i]->Y)->SetGetGameObject(*ship);
		}
		_arr_of_ships.push_back(ship);
	}

	 void FieldInterface::CreateMine(vector<COORD*> coord) {

		Bomb *bomb = new Bomb;
		for (size_t i = 0; i < coord.size(); i++)
		{
			bomb->GetArrayOfCells()->push_back(GetCellByCoord(coord[i]->X, coord[i]->Y));
			GetCellByCoord(coord[i]->X, coord[i]->Y)->SetGetGameObject(*bomb);
		}
		_arr_of_ships.push_back(bomb);
	}

	Cell* FieldInterface::GetCellByCoord(int x, int y) {
		return _arr_of_cells[x * 10 + y];
	}
	bool FieldInterface::IsEmpty(int x, int y) {
		return  GetCellByCoord(x, y)->IsEmpty();
	}

	bool FieldInterface::AreSurraundionCellsEmpty(int x, int y) {// можем ли мы поставить кораюль
		vector<Cell*> surrounding_cells;
		if (IsEmpty(x, y)) {
			surrounding_cells = GetCellByCoord(x, y)->GetSurroundingCells();
		}
		else { return false; }
		for (size_t i = 0; i < surrounding_cells.size(); i++)
		{
			if (!surrounding_cells[i]->IsEmpty()) {
				return false;
			}
		}
		return true;
	}

	void FieldInterface::ProcessShot(Shot &shot) {
		GetCellByCoord(shot.GetX(), shot.GetY())->ProcessShot(shot);
	}




	UserField::UserField(int x_shift, int y_shift) {
		_x_shift = x_shift;
		_y_shift = y_shift;
	}
	void UserField::PrintField() {

		for (size_t i = 0; i < _arr_of_cells.size(); i++)
		{
			_arr_of_cells[i]->Print(RGB(0, 255, 255));
		}
		
	}



	EnemyField::EnemyField(int x_shift, int y_shift) {
		_x_shift = x_shift;
		_y_shift = y_shift;
	}
	void EnemyField::PrintField() {

		for (size_t i = 0; i < _arr_of_cells.size(); i++)
		{
			_arr_of_cells[i]->Print(RGB(0, 255, 255));
		}
	}


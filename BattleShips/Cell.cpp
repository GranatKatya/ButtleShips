#pragma once

#include "stdafx.h"


Cell::Cell(int x, int y, int x_shift , int y_shift ) {
		_x = x;
		_y = y;
		_x_shift = x_shift;
		_y_shift = y_shift;

	}
Cell::Cell() {}


	bool Cell::IsEmpty() {
		if (gameobject == nullptr) {
			return true;
		}
		return false;
	}

	void Cell::TransformCoord(COORD &coord) { // Transform logical coords into pixels

		coord.X = _x_shift + (this->_width*this->_x);
		coord.Y = _y_shift + (this->_height*this->_y);

	}
	void Cell::Print(COLORREF color) {

		HWND myconsole = GetConsoleWindow();
		HDC mydc = GetDC(myconsole);

		COORD coord;
		TransformCoord(coord);


		for (int i = 1; i < _width - 1; ++i)
		{
			for (int j = 1; j < _height - 1; ++j)
			{
				SetPixel(mydc, coord.X + i, coord.Y + j, color);

			}
		}

		ReleaseDC(myconsole, mydc);
	}

	vector <Cell*> Cell::GetSurroundingCells() {
		vector <Cell*> surroundingCells;
		if (_right_cell != nullptr) {
			surroundingCells.push_back(_right_cell);
			if (_right_cell->GetD() != nullptr) {
				surroundingCells.push_back(_right_cell->GetD());
			}
		}
		if (_left_cell != nullptr) {
			surroundingCells.push_back(_left_cell);
			if (_left_cell->GetU() != nullptr) {
				surroundingCells.push_back(_left_cell->GetU());
			}

		}

		if (_up_cell != nullptr) {
			surroundingCells.push_back(_up_cell);
			if (_up_cell->GetR() != nullptr) {
				surroundingCells.push_back(_up_cell->GetR());
			}
		}
		if (_down_cell != nullptr) {
			surroundingCells.push_back(_down_cell);
			if (_down_cell->GetL() != nullptr) {
				surroundingCells.push_back(_down_cell->GetL());
			}
		}

		return surroundingCells;
	}
	vector <Cell*> Cell::GetAdjacentCells() {
		vector <Cell*> surroundingCells;

		if (_right_cell != nullptr) {
			surroundingCells.push_back(_right_cell);

		}
		if (_left_cell != nullptr) {
			surroundingCells.push_back(_left_cell);


		}

		if (_up_cell != nullptr) {
			surroundingCells.push_back(_up_cell);

		}
		if (_down_cell != nullptr) {
			surroundingCells.push_back(_down_cell);

		}


		return surroundingCells;
	}

	GameObject* Cell::GetContent() {//=????????????
		return gameobject;
	}

	bool Cell::GetIsShut() {
		return _isShut;
	}


	void Cell::ProcessShot(Shot &shot) { // constructor copy
		_isShut = true;
		if (gameobject == nullptr) {//������ 
			PrintMiss();
			shot.SetResult(0);
		}
		else {
			gameobject->ProcessShot(shot);
			//gameobject->PrintShutObject(shot.GetX, shot.GetY);
		}


	}

	void Cell::PrintMiss() {//������ 
		HWND myconsole = GetConsoleWindow();
		HDC mydc = GetDC(myconsole);

		COORD coord;
		TransformCoord(coord);

		for (int i = 3; i < 7; ++i)
		{
			for (int j = 3; j < 7; ++j)
			{
				if ((i + j >8 && i + j <11) && (i - j <2 && j - i <2)) {
					SetPixel(mydc, coord.X + i, coord.Y + j, RGB(211, 211, 211));//LightGray
				}

			}
		}
		ReleaseDC(myconsole, mydc);

	}

	void Cell::PrintMine() {	//bomb not killed
		HWND myconsole = GetConsoleWindow();
		HDC mydc = GetDC(myconsole);

		COORD coord;
		TransformCoord(coord);

		for (int i = 2; i < 8; ++i)
		{
			for (int i = 0; i < 10; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					if (((5 - i) * (5 - i) + (5 - j) * (5 - j)) <= 16) {
						SetPixel(mydc, coord.X + i, coord.Y + j, RGB(127, 255, 212));//Aquamarine
					}
				}
			}

		}
		ReleaseDC(myconsole, mydc);
	}

	void Cell::SetR(Cell *right_cell) { _right_cell = right_cell; }
	void Cell::SetL(Cell *left_cell) { _left_cell = left_cell; }
	void Cell::SetU(Cell *up_cell) { _up_cell = up_cell; }
	void Cell::SetD(Cell *down_cell) { _down_cell = down_cell; }

	Cell* Cell::GetR() { return _right_cell; }
	Cell* Cell::GetL() { return _left_cell; }
	Cell *Cell::GetU() { return _up_cell; }
	Cell *Cell::GetD() { return _down_cell; }

	int Cell::GetX() { return _x; }
	int Cell::GetY() { return _y; }


	void Cell::SetX(int x) { _x = x; }
	void Cell::SetY(int y) { _y = y; }

	GameObject *Cell::GetGameObject() { return gameobject; }
	void Cell::SetGetGameObject(GameObject& g) { gameobject = &g; }


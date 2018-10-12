#pragma once

#include "stdafx.h"
class GameObject;
class Shot;

extern bool templates[20][20][20];


class Cell {

	int _x;
	int _y;
	int _width = 20;
	int _height = 20;

	int _x_shift =10; // смещение поля от края
	int _y_shift =10;
	//COLORREF _color;

	bool _isShut = false;

	Cell * _right_cell = nullptr;
	Cell * _left_cell = nullptr;
	Cell * _up_cell = nullptr;
	Cell * _down_cell = nullptr;

	GameObject * gameobject = nullptr;
public:
	
	Cell(int x, int y, int _x_shift = 10, int _y_shift = 10);
	Cell();


	bool IsEmpty();

	void TransformCoord(COORD &coord);
	void Print(COLORREF color);

	vector <Cell*> GetSurroundingCells();
	vector <Cell*> GetAdjacentCells();

	GameObject* GetContent();

	bool GetIsShut();


	void ProcessShot(Shot &shot);

	void PrintMiss();

	void PrintMine();

	void SetR(Cell *right_cell);
	void SetL(Cell *left_cell);
	void SetU(Cell *up_cell);
	void SetD(Cell *down_cell);

	Cell *GetR();
	Cell *GetL();
	Cell *GetU();
	Cell *GetD();

	int GetX();
	int GetY();


	void SetX(int x);
	void SetY(int y);

	GameObject * GetGameObject();
	void SetGetGameObject(GameObject& g);


	void PrintByTemplate(COLORREF color, int index1) {

		HWND myconsole = GetConsoleWindow();
		HDC mydc = GetDC(myconsole);

		COORD coord;
		TransformCoord(coord);

		for (int i = 0; i < 20; ++i)
		{
			for (int j = 0; j < 20; ++j) {
				if (templates[index1][j][i]) {
					SetPixel(mydc, coord.X + i, coord.Y + j, color);
				}
			}
		}
		ReleaseDC(myconsole, mydc);
	}


};




#pragma once
#include "stdafx.h"
//
//HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
//

void SetColor(int text, int background);


class Menu {
	char _array[3][20] = {
    { "Play " } ,
	{ "Options" },
	{ "Exit" } };

	int _selectedItem = 0;
	//Game game;

public:
	void Print_Array() {
		Clean();
		for (int i = 0; i < 3; i++) {
			SetColor(10, 0);
			GotoXY(40, 12 + i);
			if (_selectedItem == i) { SetColor(12, 0);  cout << "+    "; cout << _array[i]; SetColor(10, 0); }
			else cout << _array[i];
		}
	}
	void Clean() {
		for (int i = 0; i < 3; i++) {
			SetColor(10, 0);
			GotoXY(40, 12 + i);
			cout << "                                                              ";
		}
	}

	int GetSelectedItem() {
		return _selectedItem;
	}

	void SetSelectedItem(int selectedItem) {
		if (selectedItem > 2) { selectedItem = 0; }
		else if (selectedItem < 0) { selectedItem = 2; }
		_selectedItem = selectedItem;
	}

	void GetClick() {

		while (1) {
			if (_kbhit())
			{
				Keys key = Console::GetKey();
				switch (key)
				{
				case Keys::ArrowUp:
					SetSelectedItem(_selectedItem - 1);

					Print_Array();
					break;

				case Keys::ArrowDown:
					SetSelectedItem(_selectedItem + 1);
					Print_Array();
					break;

				case Keys::Enter:
					Clean();
					return;
				default:
					break;
				}

			}
		}
	}
};
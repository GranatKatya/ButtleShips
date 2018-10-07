
#include "stdafx.h"

	GameObject::GameObject() {}

	vector<Cell*> *GameObject::GetArrayOfCells() { return &arr_of_cells; }

	bool GameObject::IsDead() {
		for (size_t i = 0; i < arr_of_cells.size(); i++)
		{
			if (arr_of_cells[i]->GetIsShut() == false) {
				return false;
			}
		}
		return true;
	}


	 void Ship::ProcessShot(Shot &shot) {//
		if (IsDead() == true) {

			shot.SetResult(2);
		}
		else {
			shot.SetResult(1);
		}
		PrintShutObject(shot.GetX(), shot.GetY());
	}
	 void Ship::PrintShutObject(int x, int y) {
		for (size_t i = 0; i < arr_of_cells.size(); i++) // Print wounded cell
		{
			if (arr_of_cells[i]->GetX() == x && arr_of_cells[i]->GetY() == y) {
				arr_of_cells[i]->Print(RGB(255, 255, 0));
			}
		}

		if (IsDead()) {
			for (size_t i = 0; i < arr_of_cells.size(); i++)
			{
				arr_of_cells[i]->Print(RGB(255, 0, 0));
			}
		}
	}// ¡»«Õ≈ ÀŒ√» ¿
	 void Ship::PrintGameObject() {
		for (size_t i = 0; i < arr_of_cells.size(); i++)
		{
			arr_of_cells[i]->Print(RGB(0, 255, 0));
		}
	}


	void Bomb::ProcessShot(Shot &shot) {
		shot.SetResult(3);
		PrintShutObject(shot.GetX(), shot.GetY());
	}
	 void Bomb:: PrintShutObject(int x, int y) {
		arr_of_cells[0]->Print(RGB(128, 0, 0));
	}
	 void Bomb::PrintGameObject() {
		arr_of_cells[0]->PrintMine();
	}

#pragma once

#include "stdafx.h"

class GameObject {

protected:vector<Cell*> arr_of_cells; // - проставить  

public:
	GameObject();
	vector<Cell*> *GetArrayOfCells();

	bool IsDead();
	virtual void ProcessShot(Shot &shot) = 0;
	virtual void PrintShutObject(int x, int y) = 0;
	virtual void PrintGameObject() = 0;

	virtual int ObjectType() = 0;
	

};

class Ship : public GameObject {

public:
	Ship() {}
	virtual void ProcessShot(Shot &shot);
	virtual void PrintShutObject(int x, int y);
	virtual void PrintGameObject();
	virtual int ObjectType() {
		return 1;
	}


};


class Bomb : public GameObject {

public:
	Bomb() {}
	virtual void ProcessShot(Shot &shot);

	virtual void PrintShutObject(int x, int y);
	virtual void PrintGameObject();

	virtual int ObjectType() {
		return 2;
	}
};
#pragma once

#include"stdafx.h"
class Shot {
	int _result;
	int _x;
	int _y;

public:
	Shot();
	int GetResult();
	int GetX();
	int GetY();

	void SetResult(int result);
	void SetX(int x);
	void SetY(int y);
};



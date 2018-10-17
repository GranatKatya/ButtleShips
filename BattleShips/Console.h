#pragma once
#include "stdafx.h"

class Console
{
	static HANDLE h;

public:
	static void SetColor(ForegroundColor fColor, BackgroundColor bColor)
	{
		SetConsoleTextAttribute(h, (int)fColor | (int)bColor);
	}

	static void SetCoord(short x, short y)
	{
		SetConsoleCursorPosition(h, COORD{ x, y });
	}

	static Keys GetKey()
	{
		Keys key = (Keys)_getch();

		if (key == Keys::Arrow)
			key = (Keys)_getch();

		return key;
	}
};

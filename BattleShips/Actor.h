#pragma once


#include "stdafx.h"

class Actor {

public:
	virtual void Move() = 0;
	virtual void SetUpFleet() = 0;
};

class  Enemy : public Actor {

	InterfaceIntelligence *ii = nullptr;
public:
	virtual void Move() {}
	virtual void SetUpFleet() {}

};



class User : public Actor {
	INput * _input = nullptr;

public:
	User(INput * input) {
		_input = input;
	}
	virtual void Move() {
		_input->RequestShot();

	}
	virtual void SetUpFleet() {
		_input->SetUpFleet();
	}

};


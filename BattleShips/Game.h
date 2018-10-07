#pragma once

#include "stdafx.h"

class Game {
	FieldInterface  *fieldEnemy = new  EnemyField(750, 10);
	FieldInterface *fieldUser = new UserField(500, 10);
	INput *input = new INput(fieldUser, fieldEnemy);

	//Actor * enemy = new Enemy;
	//Actor * enemy = new User(input);

	InterfaceIntelligence * ii = new SimpleIntelligence(*fieldEnemy, *fieldUser);
	void InitializedGame() {
		fieldEnemy->InitializeField();
		fieldUser->InitializeField();

		fieldUser->PrintField();
		fieldEnemy->PrintField();

		ii->SetUpFleet();
		input->SetUpFleet();

		
	}


public:
	

	void Run() {
		InitializedGame();

		while (1) {

			while (1) {//user
				input->RequestShot();// user
				fieldEnemy->ProcessShot(input->GetShot());

				if (input->GetShot().GetResult() == 0) {
					break;

				}
				else if (input->GetShot().GetResult() == 4) {
					break;
					//mine
				}

				//win

			}

			while (1) {//enemy
				ii->RandomTurn();
				fieldUser->ProcessShot(ii->GetShot());

				if (ii->GetShot().GetResult() == 0) {
					break;

				}
				else if (ii->GetShot().GetResult() == 4) {
					break;
					//mine
				}

				//win
			}
		
		}
	}
};


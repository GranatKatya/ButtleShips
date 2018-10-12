#pragma once

#include "stdafx.h"

//bool templates[10][20][20];

class Game {
	FieldInterface  *fieldEnemy = new  EnemyField(750, 40);
	FieldInterface *fieldUser = new UserField(500, 40);
	INput *input = new INput(fieldUser, fieldEnemy);

	//Actor * enemy = new Enemy;
	//Actor * enemy = new User(input);

	//InterfaceIntelligence * ii = new SimpleIntelligence(*fieldEnemy, *fieldUser);
	InterfaceIntelligence * ii = new HardIntelligence(*fieldEnemy, *fieldUser);
	void InitializedGame() {
		fieldEnemy->InitializeField();
		fieldUser->InitializeField();

		fieldUser->PrintField();
		fieldEnemy->PrintField();

		ii->SetUpFleet();
		input->SetUpFleet();

	}


public:
	

	bool IsFleetDestroed(FieldInterface * actor) {

		vector<Cell*>  unshut_cells = actor->GetUnshutsCellsFromShips();
		if (unshut_cells.size() == 0) {
			return true;
		}
		return false;
	}


	void Run() {
		InitializedGame();

		while (1) {
			
			//IsFleetDestroed(fieldUser);



			while (1) {//user
				if (IsFleetDestroed(fieldEnemy)) {
					cout << "GameOver " << endl <<"You win"<<endl;
					exit(0);
				}
				

				input->RequestShot();// user
				fieldEnemy->ProcessShot(input->GetShot());

				if (input->GetShot().GetResult() == 0) {
					break;

				}
				else if (input->GetShot().GetResult() == 3) {			
					input->RequestShipToExploude();
					fieldUser->ProcessShot(input->GetShot());

					break;
					//mine
				}
				
				//win

			}

			while (1) {//
				//IsFleetDestroed(fieldUser);
				if (IsFleetDestroed(fieldUser)) {
					cout << "GameOver " << endl << "You lose" << endl;
					exit(0);
				}

				ii->RandomTurn();
				fieldUser->ProcessShot(ii->GetShot());

				if (ii->GetShot().GetResult() == 0) {
					break;

				}
				else if (ii->GetShot().GetResult() == 3) {
					ii->RequestShipToExploude(); // DOES NOT WORK !!!
					fieldEnemy->ProcessShot(ii->GetShot());
					
					break;
					//mine
				}

				//win
			}
		
		}
	}
};











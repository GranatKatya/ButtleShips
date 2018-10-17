#pragma once
#include "stdafx.h"


//bool templates[10][20][20];


class ProgectInnterface {
protected : static IntelligenceFactory *_factory ;
public:
	virtual void  Run() = 0;
	virtual void SetIntelligenceFactory(IntelligenceFactory * factory) {
		_factory = factory;
	}

};


class Game : public ProgectInnterface {
	FieldInterface  *fieldEnemy = new  EnemyField(750, 40);
	FieldInterface *fieldUser = new UserField(500, 40);
	INput *input = new INput(fieldUser, fieldEnemy);
	InterfaceIntelligence * ii = nullptr;// = new HardIntelligence(*fieldEnemy, *fieldUser);

	void InitializedGame() {
		fieldEnemy->InitializeField();
		fieldUser->InitializeField();

		fieldUser->PrintField();
		fieldEnemy->PrintField();

		ii = _factory->createIntelligence(*fieldEnemy, *fieldUser);

		ii->SetUpFleet();
		input->SetUpFleet();

	}


	Game() {}
	static Game* game;

public:
	static Game* CreateGame(IntelligenceFactory *factory) {
		if (game == nullptr) {			
			game = new  Game();	
			_factory = factory;
			return game;
		}
	}

	bool IsFleetDestroed(FieldInterface * actor) {

		vector<Cell*>  unshut_cells = actor->GetUnshutsCellsFromShips();
		if (unshut_cells.size() == 0) {
			return true;
		}
		return false;
	}

	
	virtual void Run() {
		InitializedGame();

		while (1) {

			//IsFleetDestroed(fieldUser);



			while (1) {//user
				if (IsFleetDestroed(fieldEnemy)) {
					cout << "GameOver " << endl << "You win" << endl;
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


class ProxyForGame : public ProgectInnterface {
	 
	Game *game = nullptr;// Game::CreateGame();
	//IntelligenceFactory *factory;
public:
	ProxyForGame(IntelligenceFactory *factory) {
		_factory = factory;
	}
	/*virtual void SetIntelligenceFactory(IntelligenceFactory * factory) {
		_factory = factory;
	}*/
	virtual void  Run() {
		if (game == nullptr) {
			game = Game::CreateGame(_factory);
		}
		game->Run();
	}

};


// Game* Game::game = nullptr;











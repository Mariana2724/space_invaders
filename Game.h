#pragma once
#include "GameStatus.h"

class Game:public GameStatusUI{
	bool run_Game;
public: 
	static int SpaceShip;
	static int GameState;
	Game();
	void start(void);
	int menu(void);
	void GameName(void);
	int ChooseSpaceship(void);
	bool GameIsPaused();
	int GameIsOver(void);
	int WinGame(void);
	int InsertName(void);
	int run(void);
};
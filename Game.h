#pragma once
#include "GameStatus.h"

class Game:public GameStatusUI{
	
	bool run_Game;
protected:
	
	//static string PlayerName[20];
public: 
	static int GameState;
	Game();
	void start(void);
	int menu(void);
	void GameName(void);
	int ChooseSpaceship(void);
	bool GameIsPaused();
	int GameIsOver(void);
	int InsertName(void);
	int run(void);
};
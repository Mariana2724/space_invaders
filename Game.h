#pragma once
#include "GameStatus.h"

class Game:public GameStatusUI{
	static int GameState;
	bool run_Game;
protected:
	
	//static string PlayerName[20];
public: 
	static int SpaceShip;
	/*static int GameScore;
	static int LivesPlayer;*/
	Game();
	/*static int LivesP();
	static int Score();*/
	void start(void);
	int menu(void);
	void GameName(void);
	int ChooseSpaceship(void);
	bool GameIsPaused();
	int GameIsOver(void);
	int InsertName(void);
	int run(void);
};
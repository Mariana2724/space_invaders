#pragma once

class Game {

	static int GameState;
	bool run_Game;
protected:
	static int SpaceShip;
	static int flagmudança;
	//static string PlayerName[20];
public: 
	static int GameScore;
	static int LivesPlayer;
	Game();
	static int LivesP();
	static int Score();
	int run(void);
	int menu(void);
	int ChooseSpaceship(void);
	int GameIsPaused(void);
	int GameIsOver(void);
	int InsertName(void);
	void start(void);
	virtual void draw() {};
	virtual void movement() {};

};
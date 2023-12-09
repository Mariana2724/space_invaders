#pragma once

class Game {
	static int GameScore;
	static int LivesPlayer;
	static int GameState;
	bool run_Game;
protected:
	static int SpaceShip;
public: 
	Game();
	static int LivesP();
	static int Score();
	int run(void);
	int menu(void);
	int ChooseSpaceship(void);
	int GameIsPaused(void);
	void start(void);
	virtual void draw() {};
	virtual void movement() {};

};
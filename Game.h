#pragma once

class Game {
	static int GameScore;
	static int LivesPlayer;
	
	bool run_Game;
protected:
	static int SpaceShip;
public: 
	Game();
	static int LivesP();
	static int Score();
	void run(void);
	void menu(void);
	void start(void);
	virtual void draw() {};
	virtual void movement() {};

};
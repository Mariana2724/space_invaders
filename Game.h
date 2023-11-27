#pragma once

class Game {
	static int GameScore;
	static int LivesPlayer;
	bool run_Game;
public: 
	Game();
	static int LivesP();
	static int Score();
	void run(void);


	virtual void draw() {};
	virtual void movement() {};
	//startGame()
	//runGame()
};
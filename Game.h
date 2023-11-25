#pragma once

class Game {
	static int GameScore;
	static int LivesPlayer;
public:
	static int LivesP();
	static int Score();
	virtual void draw() = 0;
	virtual void movement() {};
};
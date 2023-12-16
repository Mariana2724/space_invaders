#pragma once
class GameStatus {
public:
	GameStatus();
	static int GameScore;
	static int LivesPlayer;
	static int xMax;
	static int yMax;
	//static string name;
	static int LivesP();
	static int Score();
	
};

class GameStatusUI : public GameStatus {
public:
	GameStatusUI();
	void GameWindow();
	void UpdateInfoScreen(); //vai escrever a informação no ecrã
};
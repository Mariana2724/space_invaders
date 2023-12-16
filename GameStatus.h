#pragma once
class GameStatus {
public:
	GameStatus();
	static int GameScore;
	static int LivesPlayer;
	static int xMax;
	static int yMax;
	static char name[];
	//static string name;
	static int LivesP();
	static int Score();
	void ScoreListInsert();
	
	
};

class GameStatusUI : public GameStatus {
public:
	GameStatusUI();
	void GameWindow();
	void UpdateInfoScreen(); //vai escrever a informação no ecrã
	void ScoreListShow();
};
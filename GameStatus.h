#pragma once
#include <vector>
#include <string>
using namespace std;

struct PlayerData {
	string UserName;
	int UserScore;
};

class GameStatus {
protected:
	vector<PlayerData>dados;
public:
	GameStatus();
	static int GameScore;
	static int LivesPlayer;
	static int xMax;
	static int yMax;
	static int Level;
	static char name[];
	//static int LivesP();
	//static int Score();
	void ScoreListInsert();
	void OrganizeScore(void);
	bool isOver(void);
};

class GameStatusUI : public GameStatus {
public:
	GameStatusUI();
	void GameWindow();
	void UpdateInfoScreen(); //vai escrever a informação no ecrã
	int ScoreListShow(void);
	
};


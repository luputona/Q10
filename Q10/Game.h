#pragma once
#include<cstdio>
#include<cstring>
#include<conio.h>
#include<ctime>
#include"Player.h"
#include"Enemy.h"
#include"Screen.h"
#include"Bullet.h"


#define MSG_MAX 100
#define STAY_TIME 3000
#define LIMIT_TIME 10000 //10초
#define MAX_STAGE 10

enum GAME_STATE
{
	INIT,
	READY,
	RUNNING,
	STOP,
	SUCCESS,
	FAILED,
	RESULT,
	CLEAR
};
struct StageInfo
{
	int nEnemyTotalCnt;		//적 최대 수
	clock_t limitTime;	//제한 시간
	int nEnemyPostLen;	//적 길이
	int nEnemyPostX;		//적 이동 x좌표
	int nEnemyPostY;		//적 이동 y좌표
	clock_t moveTime;	//적 이동 시간 간격
	int nDist;			//적 이동 거리
};

struct GameData
{
	bool isColl;
	int nStage;
	int nTotalEnemy;
	clock_t starTime;
	clock_t oldTime;
	GAME_STATE gameState;
	clock_t limitTime;	
	char strMessage[MSG_MAX];
	char strTime[MSG_MAX];
};

class Game
{
private:
	GameData gameData;
	StageInfo *pInfo;
	/*Bullet &bullet;
	Player &player;
	Enemy &enemy;
	Screen &screen;*/
public:
	Game();
	~Game();

	void Init();
	void Update();
	void Render();
	void Release();
	void WaitRender(clock_t oldTime); //화면 출력 지연
	int GetKeyEvent();
	void KeyProcess();
	
	
};
 
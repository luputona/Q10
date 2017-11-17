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
#define LIMIT_TIME 10000 //10��
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
	int nEnemyTotalCnt;		//�� �ִ� ��
	clock_t limitTime;	//���� �ð�
	int nEnemyPostLen;	//�� ����
	int nEnemyPostX;		//�� �̵� x��ǥ
	int nEnemyPostY;		//�� �̵� y��ǥ
	clock_t moveTime;	//�� �̵� �ð� ����
	int nDist;			//�� �̵� �Ÿ�
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
	void WaitRender(clock_t oldTime); //ȭ�� ��� ����
	int GetKeyEvent();
	void KeyProcess();
	
	
};
 
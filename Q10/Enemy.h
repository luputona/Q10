#pragma once
#include"Player.h"
#include"Screen.h"
#include<ctime>
#define LINE_X_MAX 7

struct EnemyData
{
	Position pos;
	clock_t moveTime;
	clock_t oldTime;
	int nLength;
	int nLineX[LINE_X_MAX];
	int nDist;
	int nHp;
};

struct StageInfo;

class Enemy
{
public:
	Enemy();
	~Enemy();


	void Init(StageInfo &info);
	void Draw();
	void Update(clock_t curTime);
	void SetPosition(int x, int y);
	void SetMoveTime(clock_t time);
	void SetOldTime(clock_t time);
	void SetLength(int len);
	void SetDistance(int dist);
	void SetHp(int hp);

	void SetLineX(int idx, int val);
	Position &GetPosition();
	clock_t GetMoveTime();
	clock_t GetOldTime();
	int GetLength();
	int GetDistance();
	int GetLineX(int idx);
	int GetHp();

private:
	EnemyData enemyData;
	
};


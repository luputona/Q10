#include "Game.h"
#include<string>
#include<iostream>
#include<Windows.h>
using namespace std;

extern Player *pPlayer;
extern Enemy *pEnemy;
extern Screen *pScreen;
extern Bullet *pBullet;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	StageInfo stageInfo[] = {
		{1, 1000 * 20, 1, 20, 5, 100, 1}

	};
	pInfo = new StageInfo[MAX_STAGE];

	for (int i = 0; i < MAX_STAGE; i++)
	{
		pInfo[i] = stageInfo[i];
	}


	gameData.oldTime = clock();
	gameData.gameState = INIT;
	gameData.limitTime = pInfo->limitTime;
	gameData.nTotalEnemy = pInfo->nEnemyTotalCnt;

	pPlayer->Init();
	pEnemy->Init(stageInfo[0]);
	pBullet->Init();
}

void Game::Update()
{
	clock_t CurTime = clock();

	pEnemy->Update(CurTime);
	pPlayer->Update(CurTime);
	
}

void Game::Render()
{
	pScreen->Clear();

	
	//pEnemy->Draw();
	pPlayer->Draw();
	//pBullet->Draw();
	pScreen->Flipping();
}

void Game::Release()
{
	delete[] pInfo;
}

void Game::WaitRender(clock_t oldTime)
{
	clock_t curTime;

	while (true)
	{
		curTime = clock();

		if (curTime - oldTime > 33)
		{
			break;
		}
	}
}

int Game::GetKeyEvent()
{
	if (_kbhit())
	{
		return _getch();
	}

	return 0;
}

void Game::KeyProcess()
{	
	pPlayer->Fire();
	pPlayer->Move();
	
}

#include "Game.h"
#include<string>
#include<iostream>
#include<Windows.h>
using namespace std;

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

	Player::GetInstance()->Init();
	Enemy::GetInstance()->Init(pInfo[0]);
	Bullet::GetInstance()->Init();
}

void Game::Update()
{
	clock_t CurTime = clock();

	Enemy::GetInstance()->Update(CurTime);
	Player::GetInstance()->Update(CurTime);
	
}

void Game::Render()
{
	Screen::GetInstance()->Clear();

	
	Enemy::GetInstance()->Draw();
	Player::GetInstance()->Draw();
	
	Screen::GetInstance()->Flipping();
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
	Player::GetInstance()->Fire();
	Player::GetInstance()->Move();
	
}

#include<iostream>
#include"Screen.h"
#include"Game.h"
#include"Player.h"
#include"Enemy.h"
#include"Bullet.h"
#include<ctime>

Screen *pScreen;
Player *pPlayer;
Enemy *pEnemy;
Bullet *pBullet;
Game *pGame;



void main()
{
	pScreen = new Screen;
	pPlayer = new Player;
	pEnemy = new Enemy;
	pBullet = new Bullet;
	pGame = new Game;
	
	//초기화

	pScreen->Init();
	pGame->Init();

	while (true)
	{
	/*	int nkey = pGame->GetKeyEvent();

		if(nkey == 'q')
		{
			break;
		}*/
		pGame->KeyProcess();

		//데이터 갱신
		pGame->Update();
		//화면출력
		pGame->Render();
		//대기
		pGame->WaitRender(clock());
	}

	pGame->Release();
	pScreen->Release();




}
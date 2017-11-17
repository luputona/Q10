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
	
	//�ʱ�ȭ

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

		//������ ����
		pGame->Update();
		//ȭ�����
		pGame->Render();
		//���
		pGame->WaitRender(clock());
	}

	pGame->Release();
	pScreen->Release();




}
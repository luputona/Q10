#include<iostream>
#include"Screen.h"
#include"Game.h"
#include"Player.h"
#include"Enemy.h"
#include"Bullet.h"
#include"Singleton.h"
#include<ctime>


void main()
{
	Screen *pScreen = Screen::GetInstance();
	Game *pGame = Game::GetInstance();

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
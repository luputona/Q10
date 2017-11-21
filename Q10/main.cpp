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
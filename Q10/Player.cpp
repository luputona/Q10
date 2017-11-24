#include "Player.h"
#include"Bullet.h"

#pragma warning(disable : 4996)

#define PLAYER_HEAD 12
#define PLAYER_BODY 8
#define PLAYER_TAIL 6

Player::Player() : m_bulletPool(DEFAULT_BULLET_SIZE)
{
	m_index = 0;
	
}

Player::~Player()
{
}

void Player::Init()
{	
	pScreen = new Screen;
	
	SetPosition(10, 22, 10, 23, 10, 24);
	SetCenterPosition(0, 0, 4, 1, 6, 2);
	SetPlayerString("△","▲  □  ▲","◀◇■□■◇▶");


	//bullet초기화 
	for (int i = 0; i < m_bulletPool.GetAmountPool(); i++)
	{
		Object<Bullet> *pPooled = m_bulletPool.GetPooledObject(i);

		if (pPooled != NULL)
		{
			Bullet *pobj = pPooled->GetObjects();
			pobj->Init();
		}
	}


}
void Player::Update(clock_t time)
{	
	//bullet 갱신
	for (int i = 0; i < m_bulletPool.GetAmountPool(); i++)
	{
		m_pBulletObj = m_bulletPool.GetPooledObject(i);
		
		if (m_pBulletObj != NULL && m_pBulletObj->GetActive())
		{
			Bullet *pObj = m_pBulletObj->GetObjects();
			pObj->Update(time, m_pBulletObj);

			if (pObj->GetCollCheck() == true)
			{
				m_pBulletObj->SetActive(false);
			}
			else
			{
				m_pBulletObj->SetActive(true);
			}		
		}		
	}

	
}

void Player::Fire()
{	
	//bullet 발사
	if (GetAsyncKeyState(VK_SPACE))
	{
		m_pBulletObj = m_bulletPool.GetPooledObject();
		
		if (m_pBulletObj != NULL)
		{
			m_pBulletObj->SetActive(true);
			Bullet *pBullet = m_pBulletObj->GetObjects();
			pBullet->SetCollCheck(false);
			pBullet->SetPosition(GetPosition()->x, GetPosition()[0].y - 1);
			pBullet->SetOldTime(clock());		
		}
	}	
	
}

void Player::Draw()
{
	char str[50][50] = { 0, };
	int printX[PLAYER_MAX];

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		printX[i] = GetPosition()[i].x - GetCenterPos()[i].x;

		if (printX[i] < 0)
		{
			pScreen->Print(0, GetPosition()[i].y, &GetPlayerString()[i][printX[i] * -1]);
		}
		else if (GetPosition()[i].x + GetCenterPos()[i].x > GAME_MAX_WIDTH)
		{
			strncat(str[i], GetPlayerString()[i], GetStrLen()[i] - ((GetPosition()[i].x + GetCenterPos()[i].x + 1) - GAME_MAX_WIDTH));
			pScreen->Print(printX[i], GetPosition()[i].y, str[i]);
		}
		else
		{			
			pScreen->Print(printX[i], GetPosition()[i].y, GetPlayerString()[i]);
		}
	}

	//bullet 그리기
	for (int i = 0; i < m_bulletPool.GetAmountPool(); i++)
	{
		Object<Bullet> * pPooled = m_bulletPool.GetPooledObject(i);

		if (pPooled != NULL && pPooled->GetActive())
		{
			Bullet * pObj = pPooled->GetObjects();
			pObj->Draw();
		}
	}

	//좌표 출력
	sprintf(str[0], " 이동 좌표1 : %d, %d  %d", GetPosition()[0].x, GetPosition()[0].y, GetCenterPos()[0].x);
	pScreen->Print(60, 2, str[0]);
	sprintf(str[1], " 이동 좌표2 : %d, %d  %d", GetPosition()[1].x, GetPosition()[1].y, GetCenterPos()[1].x);
	pScreen->Print(60, 3, str[1]);
	sprintf(str[2], " 이동 좌표3 : %d, %d  %d", GetPosition()[2].x, GetPosition()[2].y, GetCenterPos()[2].x);
	pScreen->Print(60, 4, str[2]);
}
void Player::Move()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetPosition()[0].x < 1 && GetPosition()[1].x < 1 && GetPosition()[2].x < 1)
		{
			return;
		}

		if (((GetPosition()[0].x - GetCenterPos()[0].x) < 0 || GetPosition()[0].x + ((GetCenterPos()[0].x * 2) + 1) > GAME_MAX_WIDTH) &&
			((GetPosition()[1].x - GetCenterPos()[1].x) < 0 || GetPosition()[1].x + ((GetCenterPos()[1].x * 2) + 1) > GAME_MAX_WIDTH) &&
			((GetPosition()[2].x - GetCenterPos()[2].x) < 0 || GetPosition()[2].x + ((GetCenterPos()[2].x * 2) + 1) > GAME_MAX_WIDTH))
		{

			SetPosition(--GetPosition()[0].x, GetPosition()[0].y, --GetPosition()[1].x, GetPosition()[1].y, --GetPosition()[2].x, GetPosition()[2].y);
		}
		else
		{
			SetPosition(--GetPosition()[0].x, GetPosition()[0].y, --GetPosition()[1].x, GetPosition()[1].y, --GetPosition()[2].x, GetPosition()[2].y);
		}
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if ((GetPosition()[0].x >= GAME_MAX_WIDTH - 1) && (GetPosition()[0].x >= GAME_MAX_WIDTH - 1) && (GetPosition()[0].x >= GAME_MAX_WIDTH - 1))
		{
			return;
		}
		SetPosition(++GetPosition()[0].x, GetPosition()[0].y, ++GetPosition()[1].x, GetPosition()[1].y, ++GetPosition()[2].x, GetPosition()[2].y);

		if ((GetPosition()[0].x + ((GetCenterPos()[0].x * 2) + 1) > GAME_MAX_WIDTH || (GetPosition()[0].x - GetPosition()[0].x) < 0) &&
			(GetPosition()[1].x + ((GetCenterPos()[1].x) + 1) > GAME_MAX_WIDTH || (GetPosition()[1].x - GetPosition()[1].x) < 0) &&
			(GetPosition()[2].x + ((GetCenterPos()[2].x) + 1) > GAME_MAX_WIDTH || (GetPosition()[2].x - GetPosition()[2].x) < 0))
		{
			SetPosition(++GetPosition()[0].x, GetPosition()[0].y, ++GetPosition()[1].x, GetPosition()[1].y, ++GetPosition()[2].x, GetPosition()[2].y);
		}
	}
	if (GetAsyncKeyState(VK_UP))
	{
		if (GetPosition()[0].y <= 1 && GetPosition()[1].y <= 2 && GetPosition()[2].y <= 3)
		{
			return;
		}
		SetPosition(GetPosition()[0].x, --GetPosition()[0].y, GetPosition()[1].x, --GetPosition()[1].y, GetPosition()[2].x, --GetPosition()[2].y);
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		if (GetPosition()[0].y > GAME_MAX_HEIGHT - 4 && GetPosition()[1].y >  GAME_MAX_HEIGHT - 3 && GetPosition()[2].y > GAME_MAX_HEIGHT - 2)
		{
			return;
		}
		SetPosition(GetPosition()[0].x, ++GetPosition()[0].y, GetPosition()[1].x, ++GetPosition()[1].y, GetPosition()[2].x, ++GetPosition()[2].y);
	}
}


void Player::SetPosition(int x1, int y1,int x2, int y2, int x3, int y3)
{
	playerData.pos[0].x = x1;
	playerData.pos[0].y = y1;
	playerData.pos[1].x = x2;
	playerData.pos[1].y = y2;
	playerData.pos[2].x = x3;
	playerData.pos[2].y = y3;
}

void Player::SetCenterPosition(int x1, int y1, int x2, int y2, int x3, int y3)
{
	playerData.center[0].x = x1;
	playerData.center[0].y = y1;
	playerData.center[1].x = x2;
	playerData.center[1].y = y2;
	playerData.center[2].x = x3;
	playerData.center[2].y = y3;
}
Position *Player::GetCenterPos()
{
	return playerData.center;
}
Position & Player::GetMovePosition()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return playerData.movePos;
}
Position *Player::GetPosition()
{
	return playerData.pos;
}

void Player::SetPlayerString(char *str1, char *str2, char *str3)
{
	playerData.nLength[0] = strlen(str1);
	playerData.strPlayer[0] = new char[playerData.nLength[0] + 1];
	strcpy(playerData.strPlayer[0], str1);

	playerData.nLength[1] = strlen(str2);
	playerData.strPlayer[1] = new char[playerData.nLength[1] + 1];
	strcpy(playerData.strPlayer[1], str2);

	playerData.nLength[2] = strlen(str3);
	playerData.strPlayer[2] = new char[playerData.nLength[2] + 1];
	strcpy(playerData.strPlayer[2], str3);
}
void Player::SetMovePosition(int x, int y)
{
	playerData.movePos.x = x;
	playerData.movePos.y = y;
}

int *Player::GetStrLen()
{
	return playerData.nLength;
}
char **Player::GetPlayerString()
{
	return playerData.strPlayer;
}

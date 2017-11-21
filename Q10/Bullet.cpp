#include "Bullet.h"

#include<iostream>
using namespace std;

Bullet::Bullet()
{
	
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	pScreen = new Screen;
	
	//총알 초기화
	//SetIsReady(true);
	m_collCheck = false;
	SetPosition(Player::GetInstance()->GetPosition()->x, Player::GetInstance()->GetPosition()[0].y - 1);
	SetMoveTime(30);
}

void Bullet::Draw()
{

	pScreen->Print(GetPosition().x, GetPosition().y, "◎");
}

void Bullet::Reset()
{
	//SetIsReady(true);
	SetPosition(Player::GetInstance()->GetPosition()->x, Player::GetInstance()->GetPosition()[0].y -1);
}

bool Bullet::Collision(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	if (x1 <= x4 && x2 >= x3 && y1 <= y4 && y2 >= y3) {
		return true;
	}
	else {
		return false;
	}
}

void Bullet::Update(clock_t CurTime, Object<Bullet> *pObj)
{
	Enemy * pEnemy = Enemy::GetInstance();	

	pObj = new Object<Bullet>;
	
	SetPosition(GetPosition().x, --GetPosition().y);

	if (GetPosition().y < 0)
	{
		SetCollCheck(true);	
	}	

	if (GetPosition().y >= 0)
	{		
		SetCollCheck(false);		
	}
	
	//여기다가 충돌 체크
	//발사 상태	

	//대기 상태
	/*if (pObj->GetActive())
	{
		SetPosition(pPlayer->GetPosition()->x, pPlayer->GetPosition()[0].y - 1);
		SetCollCheck(false);
	}*/

	//라인 충돌
	int x = GetPosition().x;
	int y = GetPosition().y;
	int len = 2;

	int tx = pEnemy->GetPosition().x;
	int ty = pEnemy->GetPosition().y;
	int nLen = pEnemy->GetLength() * 2 + 1;
	int tlen = pEnemy->GetLineX(2);
	
	//if (Collision(x, y, x + len, y + 1, tx, ty, tx + tlen , ty ))
	//{
	//	SetCollCheck(true);
	//	
	//	//적 hp 감소 기능 추가
	//}
		
	if (GetPosition().x >= pEnemy->GetLineX(0) && GetPosition().x + 1 <= pEnemy->GetLineX(nLen - 1))
	{
		//라인을 넘어가면 
		if (GetPosition().y <= pEnemy->GetPosition().y)
		{
			SetCollCheck(true);
			//적 hp 감소 기능 추가
		}
	}
		
	if (//왼쪽
		(GetPosition().x >= pEnemy->GetLineX(0) - 2 && GetPosition().x <= pEnemy->GetLineX(0) - 1 )||
		(GetPosition().x + 1 >= pEnemy->GetLineX(0) - 2 && GetPosition().x + 1 <= pEnemy->GetLineX(0) - 1) ||
		//오른쪽
		(GetPosition().x >= pEnemy->GetLineX(nLen - 1) + 2 && GetPosition().x <= pEnemy->GetLineX(nLen -1 ) + 2)||
		(GetPosition().x + 1 >= pEnemy->GetLineX(nLen - 1) + 2 && GetPosition().x + 1<= pEnemy->GetLineX(nLen - 1) + 2))
	{
		if (GetPosition().y <= pEnemy->GetPosition().y)
		{
			SetCollCheck(true);
			//적 hp 감소 기능 추가
		}
	}

}

void Bullet::SetIsReady(bool ready)
{
	bulletData.isReady = ready;
}

void Bullet::SetPosition(int x, int y)
{
	bulletData.pos.x = x;
	bulletData.pos.y = y;
}

void Bullet::SetMoveTime(clock_t time)
{
	bulletData.moveTime = time;
}

void Bullet::SetOldTime(clock_t time)
{
	bulletData.oldTime = time;
}

void Bullet::SetCount(int count)
{

}

void Bullet::SetIndex(int index)
{
	m_index = index;
}

void Bullet::SetValue(int val)
{
	m_value = val;
}

void Bullet::SetCollCheck(bool collcheck)
{
	m_collCheck = collcheck;
}

int Bullet::GetIndex()
{
	return m_index;
}

int Bullet::GetValue()
{
	return m_value;
}

bool Bullet::GetIsReady()
{
	return bulletData.isReady;
}

bool Bullet::GetCollCheck()
{
	return m_collCheck;
}

clock_t Bullet::GetMoveTime()
{
	return bulletData.moveTime;
}

clock_t Bullet::GetOldTime()
{
	return bulletData.oldTime;
}

Position & Bullet::GetPosition()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return bulletData.pos;
}

#include "Bullet.h"

extern Screen *pScreen;
extern Player *pPlayer;
extern Enemy *pEnemy;

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
	//총알 초기화
	//SetIsReady(true);
	SetPosition(pPlayer->GetPosition()->x, pPlayer->GetPosition()[0].y - 1);
	SetMoveTime(30);

}

void Bullet::Draw()
{
	pScreen->Print(GetPosition().x, GetPosition().y, "◎");
}

void Bullet::Reset()
{
	SetIsReady(true);
	SetPosition(pPlayer->GetPosition()->x, pPlayer->GetPosition()[0].y - 1);
}

void Bullet::Update(clock_t CurTime, Object<Bullet> *pObj)
{
	Screen sc;
	int nLen = pEnemy->GetLength() * 2 + 1;

	SetValue(GetValue() + 1);
	
	pObj = new Object<Bullet>;
	
	//여기다가 충돌 체크
	//발사 상태
	if (!pObj->GetActive())
	{
		if ((CurTime - GetOldTime()) > GetMoveTime())
		{
			if (GetPosition().y > 0)
			{				
				SetPosition(GetPosition().x, --GetPosition().y);
				SetOldTime(CurTime);				
			}
			else// if(GetPosition().y <=0 )
			{			
				pObj->SetActive(true);
				Reset();
			}
		}
	}

	//대기 상태
	if (pObj->GetActive())
	{		
		SetPosition(pPlayer->GetPosition()->x, pPlayer->GetPosition()[0].y - 1);
	}

	//라인 충돌
	if (GetPosition().x >= pEnemy->GetLineX(0) && GetPosition().x + 1 <= pEnemy->GetLineX(nLen - 1))
	{
		//라인을 넘어가면 
		if (GetPosition().y <= pEnemy->GetPosition().y)
		{			
			pObj->SetActive(true);
			Reset();
			//적 hp 감소 기능 추가
		}
	}
	
	if (//왼쪽
		(GetPosition().x >= pEnemy->GetLineX(0) - 2 && GetPosition().x <= pEnemy->GetLineX(0) - 1 )||
		(GetPosition().x + 1 >= pEnemy->GetLineX(0) - 2 && GetPosition().x + 1 <= pEnemy->GetLineX(0) - 1) ||
		//오른쪽
		(GetPosition().x >= pEnemy->GetLineX(nLen - 1) + 2 && GetPosition().x <= pEnemy->GetLineX(nLen -1 ) + 3)||
		(GetPosition().x + 1 >= pEnemy->GetLineX(nLen - 1) + 2 && GetPosition().x + 1<= pEnemy->GetLineX(nLen - 1) + 3))
	{
		if (GetPosition().y <= pEnemy->GetPosition().y)
		{			
			pObj->SetActive(true);
			Reset();			
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

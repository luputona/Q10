#include "Enemy.h"
#include"Game.h"


Enemy::Enemy() : m_bulletPool(DEFAULT_BULLET_SIZE)
{
	return;
}


Enemy::~Enemy()
{
}

void Enemy::Init(StageInfo & info)
{
	pScreen = new Screen;
	SetPosition(info.nEnemyPostX, info.nEnemyPostY); //초기 위치값
	SetLength(info.nEnemyPostLen);					 //적의 기본 길이 1
	SetMoveTime(info.moveTime);						//100ms 단위로 움직이도록 설정
	SetOldTime(clock());							//
	SetDistance(info.nDist);						//골대가 100ms 마다 움직이는 거리, 1
	SetHp(10000);

	enemyData.fireTime = rand() % 1000 + 2000;
	enemyData.oldFireTime = clock();
	int nLen = GetLength() * 2 + 1;

	//bitstream
	for (int i = 0; i < nLen; i++)
	{
		//nLineX[i]에 계산한 골 라인의 길이 (3)만큼 순서대로 라인의 좌표를 넣어준다
		SetLineX(i, GetPosition().x + 2 * (i + 1));
	}
}

void Enemy::Draw()
{
	//왼쪽 골 포스트 출력
	pScreen->Print(GetPosition().x, GetPosition().y, "□");

	// 길이만큼 라인 출력
	int nLen = GetLength() * 2 ;

	for (int i = 0; i < nLen; i++)
	{
		pScreen->Print(GetLineX(i), GetPosition().y, "■");
	}

	//라인 다음의 칼럭 (+2)에 오른쪽 네모 출력
	pScreen->Print(GetLineX(nLen - 1) + 2, GetPosition().y, "□");
	
}

void Enemy::Update(clock_t curTime)
{
	//적의 움직임
	if (curTime - GetOldTime() > GetMoveTime())
	{
		int nLen = GetLength() * 2 + 1;

		SetOldTime(curTime);
		if (GetPosition().x + GetDistance() >= 0 &&	((GetLineX(nLen - 1) + 3) + GetDistance()) <= GAME_MAX_WIDTH)
		{
			SetPosition(GetPosition().x + GetDistance(), GetPosition().y);

			for (int i = 0; i < nLen; i++)
			{
				SetLineX(i, GetPosition().x + (2 * (i + 1)));
			}
		}
		else
		{
			SetDistance(GetDistance() * -1);
		}
	}

	//발사 
	if (curTime - enemyData.oldFireTime > enemyData.fireTime )
	{
		Fire();
		enemyData.oldFireTime = curTime;
		enemyData.fireTime = rand() % 1000 + 3000;
	}
}

void Enemy::Fire()
{

	Object<Bullet> *pObj= m_bulletPool.GetPooledObject();

	if (pObj != NULL)
	{
		pObj->SetActive(true);
		Bullet *pBullet1 = pObj->GetObjects();
		pBullet1->SetCollCheck(false);
		pBullet1->SetPosition(GetPosition().x, GetPosition().y + 2);
		pBullet1->SetOldTime(clock());
	}
}

void Enemy::SetPosition(int x, int y)
{	if (x == 0 && y == 0)
	{
		return;
	}
	enemyData.pos.x = x;
	enemyData.pos.y = y;
}

void Enemy::SetMoveTime(clock_t time)
{
	enemyData.moveTime = time;
}

void Enemy::SetOldTime(clock_t time)
{
	enemyData.oldTime = time;
}

void Enemy::SetLength(int len)
{
	enemyData.nLength = len;
}

void Enemy::SetDistance(int dist)
{
	enemyData.nDist = dist;
}

void Enemy::SetHp(int hp)
{
	enemyData.nHp = hp;
}


void Enemy::SetLineX(int idx, int val)
{
	enemyData.nLineX[idx] = val;
}

Position & Enemy::GetPosition()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return enemyData.pos;
}

clock_t Enemy::GetMoveTime()
{
	return enemyData.moveTime;
}

clock_t Enemy::GetOldTime()
{
	return enemyData.oldTime;
}

int Enemy::GetLength()
{
	return enemyData.nLength;
}

int Enemy::GetDistance()
{
	return enemyData.nDist;
}

int Enemy::GetLineX(int idx)
{
	return enemyData.nLineX[idx];
}

int Enemy::GetHp()
{
	return enemyData.nHp;
}

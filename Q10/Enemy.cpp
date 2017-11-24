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
	SetPosition(info.nEnemyPostX, info.nEnemyPostY); //�ʱ� ��ġ��
	SetLength(info.nEnemyPostLen);					 //���� �⺻ ���� 1
	SetMoveTime(info.moveTime);						//100ms ������ �����̵��� ����
	SetOldTime(clock());							//
	SetDistance(info.nDist);						//��밡 100ms ���� �����̴� �Ÿ�, 1
	SetHp(10000);

	enemyData.fireTime = rand() % 1000 + 2000;
	enemyData.oldFireTime = clock();
	int nLen = GetLength() * 2 + 1;

	//bitstream
	for (int i = 0; i < nLen; i++)
	{
		//nLineX[i]�� ����� �� ������ ���� (3)��ŭ ������� ������ ��ǥ�� �־��ش�
		SetLineX(i, GetPosition().x + 2 * (i + 1));
	}
}

void Enemy::Draw()
{
	//���� �� ����Ʈ ���
	pScreen->Print(GetPosition().x, GetPosition().y, "��");

	// ���̸�ŭ ���� ���
	int nLen = GetLength() * 2 ;

	for (int i = 0; i < nLen; i++)
	{
		pScreen->Print(GetLineX(i), GetPosition().y, "��");
	}

	//���� ������ Į�� (+2)�� ������ �׸� ���
	pScreen->Print(GetLineX(nLen - 1) + 2, GetPosition().y, "��");
	
}

void Enemy::Update(clock_t curTime)
{
	//���� ������
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

	//�߻� 
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
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
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

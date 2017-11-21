#pragma once
#include<cstdio>
#include<cstring>
#include<conio.h>
#include<ctime>
#include"ObjectPool.h"
#include"Singleton.h"
#include"Screen.h"


#define PLAYER_MAX 3

struct Position
{
	int x;
	int y;
};

struct PlayerData
{
	Position pos[PLAYER_MAX];
	Position center[PLAYER_MAX];
	Position movePos;
	char *strPlayer[PLAYER_MAX];
	int nLength[PLAYER_MAX];
};

class Bullet;
class Player : public Singleton<Player>
{
private:
	PlayerData playerData;
	ObjectPool<Bullet> m_bulletPool;
	Object<Bullet> *m_pBulletObj;
	Screen *pScreen;
	//Bullet *pBullet;

	int m_index;
public:
	Player();
	~Player();

	void Init();
	void Draw();
	void SetPosition(int x1, int y1, int x2, int y2, int x3, int y3);
	void SetCenterPosition(int x1, int y1, int x2, int y2, int x3, int y3);
	void SetPlayerString(char *str1, char *str2, char *str3);
	void SetMovePosition(int x = 0, int y = 0);
	void Update(clock_t itme);
	void Fire();
	void Move();
	//void SetFireInterval(clock_t itme);
	Position *GetPosition();
	Position *GetCenterPos();
	Position &GetMovePosition();

	
	int *GetStrLen();
	char **GetPlayerString();
	//clock_t GetFireInterval();
};


#pragma once
#include"Player.h"
#include"ObjectPool.h"
#include"Screen.h"
#include"Enemy.h"
#include<ctime>

#define DEFAULT_BULLET_SIZE 40

struct BulletData
{
	bool isReady;
	Position pos;
	clock_t moveTime;
	clock_t oldTime;
	int count;
};
struct StageInfo;
class Bullet
{
private:
	BulletData bulletData;
	int m_value;
	int m_index;
public:
	Bullet();
	~Bullet();

	void Init();
	void Draw();
	void Reset();
	void Update(clock_t CurTime,Object<Bullet> *pObj);
	void SetIsReady(bool ready);
	void SetPosition(int x, int y);
	void SetMoveTime(clock_t time);
	void SetOldTime(clock_t time);
	void SetCount(int count);
	void SetIndex(int index);
	void SetValue(int val);

	int GetIndex();
	int GetValue();
	bool GetIsReady();
	clock_t GetMoveTime();
	clock_t GetOldTime();
	Position &GetPosition();
	


};


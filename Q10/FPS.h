#pragma once
#include"Screen.h"
#include<ctime>
#include<cstdio>

#define BUF_MAX 10

struct FPSData
{
	clock_t fpsCurTime;
	clock_t fpsOldTime;
	int frameCnt;
	char *fpsTextBuffer;
};

class FPS
{
public:
	FPS();
	~FPS();

	void Init();
	void Draw();
	void Destroy();

private:
	
	FPSData fpsData;

};


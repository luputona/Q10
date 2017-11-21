#pragma once
#include<Windows.h>
#include"Singleton.h"
#define GAME_MAX_WIDTH 60
#define GAME_MAX_HEIGHT 30
class Screen : public Singleton<Screen>
{
public:
	Screen();
	~Screen();

	void Init();		//초기화
	void Flipping();	//화면 버퍼 전환
	void Clear();		//화면 버퍼 지우기
	void Release();		//화면 버퍼 해제
	void Print(int x, int y, char *str);	//화면 출력
	void SetColor(unsigned short color);
};


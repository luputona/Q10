#pragma once
#include<Windows.h>
#define GAME_MAX_WIDTH 60
#define GAME_MAX_HEIGHT 30
class Screen
{
public:
	Screen();
	~Screen();

	void Init();		//�ʱ�ȭ
	void Flipping();	//ȭ�� ���� ��ȯ
	void Clear();		//ȭ�� ���� �����
	void Release();		//ȭ�� ���� ����
	void Print(int x, int y, char *str);	//ȭ�� ���
	void SetColor(unsigned short color);
};


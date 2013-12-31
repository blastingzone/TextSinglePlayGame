#pragma once
#include "config.h"


// ������� ��������. �� �� ����� ������ ���°�?
// ������. ��������(����?)
static DWORD				gPreviousCheckedTime;
static DWORD				gPresentCheckedTime;
static DWORD				gDifferentSecond;
static bool					gIsTimerWorkable = true;
// 1�ʰ� �� �� ����ߴ��� ���� ����
static int					gSecondsStack = 0;

class CTimer
{
public:
	CTimer(void);
	~CTimer(void);

	//������ �ð��� ���
	void CalcPassedTime();

	//������ �ð����� �� �ϵ��� ������
	unsigned int OnTick();

	//Ÿ�̸��� ���� / ������ ������
	static void DoTimerGo();
	static void DoTimerStop();

	//Ÿ�̸� �������� �ʱ�ȭ ��
	static void ResetTimer()			{	gDifferentSecond = 0;
									gPresentCheckedTime = 0;
									gPreviousCheckedTime = 0; }

	//Ÿ�̸Ӹ� �����忡 ����ֱ� ���� ������ ������ �κ�
	static unsigned int __stdcall ThreadEntry(void* pLPVOID);
};
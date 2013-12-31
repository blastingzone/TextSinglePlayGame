#pragma once
#include "config.h"


// 쓰레드용 전역변수. 좀 더 우아한 접근은 없는가?
// 괜찮다. 문제없어(정말?)
static DWORD				gPreviousCheckedTime;
static DWORD				gPresentCheckedTime;
static DWORD				gDifferentSecond;
static bool					gIsTimerWorkable = true;
// 1초가 몇 번 경과했는지 세는 변수
static int					gSecondsStack = 0;

class CTimer
{
public:
	CTimer(void);
	~CTimer(void);

	//지나간 시간을 계산
	void CalcPassedTime();

	//일정한 시간마다 할 일들을 정의함
	unsigned int OnTick();

	//타이머의 진행 / 멈춤을 결정함
	static void DoTimerGo();
	static void DoTimerStop();

	//타이머 변수들을 초기화 함
	static void ResetTimer()			{	gDifferentSecond = 0;
									gPresentCheckedTime = 0;
									gPreviousCheckedTime = 0; }

	//타이머를 쓰레드에 집어넣기 위해 형식을 맞춰준 부분
	static unsigned int __stdcall ThreadEntry(void* pLPVOID);
};
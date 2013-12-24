#include "stdafx.h"
#include "Timer.h"


CTimer::CTimer(void)
{
}


CTimer::~CTimer(void)
{
}


/////////////////////////////////////////////////////////////////////////////////
// Timer Part
/////////////////////////////////////////////////////////////////////////////////

unsigned int CTimer::OnTick()
{
	bool isInfinite = true;

	while (isInfinite)
	{
		// 시간 경과를 계산한다.
		CalcPassedTime();

		// 타이머가 유효하다면 일을 하고 아니면 하지 않는다.
		if (gIsTimerWorkable)
		{
			// 1초마다 해야 할 일
			if (gDifferentSecond > 1000)
			{
				printf("1초가 넘었어!\n");
				ResetTimer();
			}
		}
	}

	return 1;
}

void CTimer::CalcPassedTime()
{
	if (0 == gPreviousCheckedTime)
	{
		gPreviousCheckedTime = GetTickCount();
	}
	else
	{
		gPresentCheckedTime = GetTickCount();
		gDifferentSecond = gPresentCheckedTime - gPreviousCheckedTime;
	}
}

// 쓰레드에 넣기 위해 형식을 맞춰준다
unsigned int __stdcall WINAPI CTimer::ThreadEntry(void* pUserData)
{
	return ((CTimer*)pUserData)->OnTick();
}

// 타이머가 계속 진행하도록 설정
void CTimer::DoTimerGo()
{
	gIsTimerWorkable = true;
	ResetTimer();
}

// 타이머가 멈추도록 설정
void CTimer::DoTimerStop()
{
	gIsTimerWorkable = false;
}

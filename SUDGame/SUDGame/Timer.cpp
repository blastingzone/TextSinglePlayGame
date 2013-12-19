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

unsigned int CTimer::IsPassedOneSecond()
{
	bool isInfinite = true;

	while (isInfinite)
	{
		// 시간 경과를 계산한다.
		CalcPassedTime();
		// 1초마다 해야 할 일
		if (m_DifferentSecond > 1000)
		{
			printf("1초가 넘었어!\n");
			ResetTimer();
		}
	}

	return 1;
}

void CTimer::CalcPassedTime()
{
	if (0 == m_PreviousCheckedTime)
	{
		m_PreviousCheckedTime = GetTickCount();
	}
	else
	{
		m_PresentCheckedTime = GetTickCount();
		m_DifferentSecond = m_PresentCheckedTime - m_PreviousCheckedTime;
	}
}

unsigned int __stdcall WINAPI CTimer::ThreadEntry(void* pUserData)
{
	return ((CTimer*)pUserData)->IsPassedOneSecond();
}
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
		// �ð� ����� ����Ѵ�.
		CalcPassedTime();
		// 1�ʸ��� �ؾ� �� ��
		if (m_DifferentSecond > 1000)
		{
			printf("1�ʰ� �Ѿ���!\n");
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
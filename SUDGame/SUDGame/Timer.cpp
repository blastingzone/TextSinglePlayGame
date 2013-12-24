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
		// �ð� ����� ����Ѵ�.
		CalcPassedTime();

		// Ÿ�̸Ӱ� ��ȿ�ϴٸ� ���� �ϰ� �ƴϸ� ���� �ʴ´�.
		if (gIsTimerWorkable)
		{
			// 1�ʸ��� �ؾ� �� ��
			if (gDifferentSecond > 1000)
			{
				printf("1�ʰ� �Ѿ���!\n");
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

// �����忡 �ֱ� ���� ������ �����ش�
unsigned int __stdcall WINAPI CTimer::ThreadEntry(void* pUserData)
{
	return ((CTimer*)pUserData)->OnTick();
}

// Ÿ�̸Ӱ� ��� �����ϵ��� ����
void CTimer::DoTimerGo()
{
	gIsTimerWorkable = true;
	ResetTimer();
}

// Ÿ�̸Ӱ� ���ߵ��� ����
void CTimer::DoTimerStop()
{
	gIsTimerWorkable = false;
}

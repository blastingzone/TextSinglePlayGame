#include "stdafx.h"
#include "Timer.h"
#include "Player.h"

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
				ResetTimer();
				++gSecondsStack;
				// Fury ��ų�� Ȱ��ȭ �Ǿ� �ִٸ� ���� ������ 3�� ��´�.
				if ( CPlayer::GetInstance()->GetFuryFlag() )
				{
					// ���� ������ 3 �̸��̸� �ڵ����� ǻ���� Ǯ����.
					if ( CPlayer::GetInstance()->GetMP() < 3 )
					{
						printf_s("����� �ص��� �Ƿθ� �����ϴ�.\n");
						CPlayer::GetInstance()->TurnFuryFlag();
					}

					// Fury ��ų�� Ȱ��ȭ �Ǿ� �ִ��� ������ ������ ������ ���̴� ���� ����� �� �ִ�.
					if ( CPlayer::GetInstance()->GetINT() + ( rand() % 20 ) < 23 )
					{
						printf_s("����� �̼��� �Ұ� �� �밡�� ���͸� ��վ�ϴ�. \n");
						CPlayer::GetInstance()->RecoverStatus(0, -3);
					}
					else
					{
						printf_s("����� �̼��� ã������ �־��ϴ�. ���� �Ҹ� �����մϴ�. \n");
					}
				}
			}
			// 10�ʸ��� �ؾ� �� ��
			if (gSecondsStack >= 10)
			{
				gSecondsStack = 0;
				CPlayer::GetInstance()->RecoverStatus(5, 0);
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
	ResetTimer();
	gIsTimerWorkable = true;
}

// Ÿ�̸Ӱ� ���ߵ��� ����
void CTimer::DoTimerStop()
{
	gIsTimerWorkable = false;
}

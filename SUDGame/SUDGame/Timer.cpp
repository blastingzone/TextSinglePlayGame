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
		// 시간 경과를 계산한다.
		CalcPassedTime();

		// 타이머가 유효하다면 일을 하고 아니면 하지 않는다.
		if (gIsTimerWorkable)
		{
			// 1초마다 해야 할 일
			if (gDifferentSecond > 1000)
			{
				ResetTimer();
				++gSecondsStack;
				// Fury 스킬이 활성화 되어 있다면 매초 마나를 3씩 깎는다.
				if ( CPlayer::GetInstance()->GetFuryFlag() )
				{
					// 남은 마나가 3 미만이면 자동으로 퓨리가 풀린다.
					if ( CPlayer::GetInstance()->GetMP() < 3 )
					{
						printf_s("당신은 극도의 피로를 느낍니다.\n");
						CPlayer::GetInstance()->TurnFuryFlag();
					}

					// Fury 스킬이 활성화 되어 있더라도 지능이 높으면 마나가 깎이는 것을 방어할 수 있다.
					if ( CPlayer::GetInstance()->GetINT() + ( rand() % 20 ) < 23 )
					{
						printf_s("당신은 이성을 잃고 그 대가로 몬스터를 꿰뚫어봅니다. \n");
						CPlayer::GetInstance()->RecoverStatus(0, -3);
					}
					else
					{
						printf_s("당신은 이성을 찾으려고 애씁니다. 마나 소모에 저항합니다. \n");
					}
				}
			}
			// 10초마다 해야 할 일
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

// 쓰레드에 넣기 위해 형식을 맞춰준다
unsigned int __stdcall WINAPI CTimer::ThreadEntry(void* pUserData)
{
	return ((CTimer*)pUserData)->OnTick();
}

// 타이머가 계속 진행하도록 설정
void CTimer::DoTimerGo()
{
	ResetTimer();
	gIsTimerWorkable = true;
}

// 타이머가 멈추도록 설정
void CTimer::DoTimerStop()
{
	gIsTimerWorkable = false;
}

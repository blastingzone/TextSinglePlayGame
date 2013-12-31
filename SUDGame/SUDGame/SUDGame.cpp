// SUDGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameInput.h"
#include "Player.h"
#include "GameMap.h"
#include "GameMaster.h"
#include "Timer.h"
#include <crtdbg.h>
#include <time.h>
#include <process.h>

// 메모리 누수 체크
#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

// C style 함수 선언
void PrintNormalScreenUI(CGameMaster GM);
void PrintFurySkillUI(CGameMaster GM);

int _tmain(int argc, _TCHAR* argv[])
{
	argc;
	argv;

	// 메모리 누수 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 랜덤 테이블 생성. 두고두고 쓴다.
	srand( static_cast<unsigned int>( time(NULL) ) );

	CGameMaster GM;
	CTimer* TM = new CTimer();

	// 세계지도 초기화
	CGameMap::GetInstance()->InitMap();
	GM.CreateAndLocaleMonsters();
	getchar();

	// 현 위치를 출력하기 위한 쓰레드
	 HANDLE hHandle;
	 DWORD TimerThreadAddr;
	 hHandle = (HANDLE)_beginthreadex(NULL, 0, TM->ThreadEntry, NULL, 0, (unsigned int*)(&TimerThreadAddr) );

 	if ( hHandle == INVALID_HANDLE_VALUE )
	{
 		printf("Timer Error!\n");
 	}

	// 엔딩 종류를 결정하기 위한 변수
	ENDING_TYPE Ending = CONTINUE_GAME;

	// 메인 루프
	do
	{
		// Fury 스킬에 따라 UI가 달라진다. Fury 모드에서는 몬스터 위치가 보인다.
		if ( CPlayer::GetInstance()->GetFuryFlag() )
		{
			PrintFurySkillUI(GM);
		}
		else
		{
			PrintNormalScreenUI(GM);
		}
		// 엔딩 조건 검사
		Ending = GM.GameEndCheck();
		// 만약 엔딩조건에 해당될 경우 loop 탈출 및 엔딩
		// 타이머도 멈춘다.
		if ( Ending != CONTINUE_GAME )
		{
			TM->DoTimerStop();
			break;
		}
	}
	while(CGameInput::GetInstance()->CommandInput());

	// 엔딩
	GM.EndingScene(Ending);

	// 사용된 싱글톤을 해제
	CPlayer::GetInstance()->ReleaseInstance();
	CGameMap::GetInstance()->DeleteAllMonster();
	CGameMap::GetInstance()->ReleaseInstance();
	CGameInput::GetInstance()->ReleaseInstance();
	
	// 타이머를 파.괴.한.다.
	delete TM;

	// 핸들을 닫는다
	CloseHandle(hHandle);

	return 0;
}

void PrintNormalScreenUI(CGameMaster GM)
{
	//콘솔 화면을 지우는 명령어
	system("cls");

	CPlayer::GetInstance()->PrintPosition();
	CGameMap::GetInstance()->PrintMap();
	CPlayer::GetInstance()->PrintStatusUI();
	CGameMap::GetInstance()->GetMapType(CPlayer::GetInstance()->GetPosition())->Render();

	//몬스터가 있다면 여기서 전투 시작
	GM.CheckMob(CPlayer::GetInstance()->GetPosition());
}

void PrintFurySkillUI(CGameMaster GM)
{
	system("cls");
	printf_s("\n Fury 모드를 종료하려면 f 키를 누르세요! \n");
	CPlayer::GetInstance()->PrintPosition();
	CGameMap::GetInstance()->PrintFurySkillMap();
	CPlayer::GetInstance()->PrintStatusUI();
	CGameMap::GetInstance()->GetMapType(CPlayer::GetInstance()->GetPosition())->Render();

	//몬스터가 있다면 여기서 전투 시작
	GM.CheckMob(CPlayer::GetInstance()->GetPosition());
}
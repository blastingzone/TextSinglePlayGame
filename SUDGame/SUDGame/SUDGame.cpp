// SUDGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameInput.h"
#include "Player.h"
#include "GameMap.h"
#include "GameMaster.h"
#include <crtdbg.h>
#include <time.h>

// 메모리 누수 체크
#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	argc;
	argv;

	// 메모리 누수 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 랜덤 테이블 생성
	srand( static_cast<unsigned int>( time(NULL) ) );

	CGameMaster GM;
	// 세계지도 초기화
	CGameMap::GetInstance()->InitMap();
	GM.CreateAndLocaleMonsters();
	getchar();

	// 메인 루프
	do
	{
		//콘솔 화면을 지우는 명령어
		system("cls");
		CPlayer::GetInstance()->PrintPosition();
		CGameMap::GetInstance()->PrintMap();
		CGameMap::GetInstance()->GetMapType(CPlayer::GetInstance()->GetPosition())->Render();
		GM.CheckMob(CPlayer::GetInstance()->GetPosition());
		CPlayer::GetInstance()->PrintStatusUI();
	}
	while(CGameInput::GetInstance()->CommandInput());


	// 사용된 싱글톤을 해제
	CPlayer::GetInstance()->ReleaseInstance();
	CGameMap::GetInstance()->DeleteAllMonster();
	CGameMap::GetInstance()->ReleaseInstance();
	CGameInput::GetInstance()->ReleaseInstance();

	return 0;
}


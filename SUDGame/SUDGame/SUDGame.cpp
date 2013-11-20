// SUDGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameInput.h"
#include "Player.h"
#include "GameMap.h"
#include "GameMaster.h"
#include <crtdbg.h>
// 메모리 누수 체크
#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	// 메모리 누수 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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
	}
	while(CGameInput::GetInstance()->CommandInput());

	return 0;
}


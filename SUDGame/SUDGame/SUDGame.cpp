// SUDGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameInput.h"
#include "Player.h"
#include "GameMap.h"
#include "GameMaster.h"
#include <crtdbg.h>
#include <time.h>

// �޸� ���� üũ
#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	argc;
	argv;

	// �޸� ���� üũ
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ���� ���̺� ����
	srand( static_cast<unsigned int>( time(NULL) ) );

	CGameMaster GM;
	// �������� �ʱ�ȭ
	CGameMap::GetInstance()->InitMap();
	GM.CreateAndLocaleMonsters();
	getchar();

	// ���� ����
	do
	{
		//�ܼ� ȭ���� ����� ��ɾ�
		system("cls");
		CPlayer::GetInstance()->PrintPosition();
		CGameMap::GetInstance()->PrintMap();
		CGameMap::GetInstance()->GetMapType(CPlayer::GetInstance()->GetPosition())->Render();
		GM.CheckMob(CPlayer::GetInstance()->GetPosition());
	}
	while(CGameInput::GetInstance()->CommandInput());


	// ���� �̱����� ����
	CPlayer::GetInstance()->ReleaseInstance();
	CGameMap::GetInstance()->DeleteAllMonster();
	CGameMap::GetInstance()->ReleaseInstance();
	CGameInput::GetInstance()->ReleaseInstance();

	return 0;
}


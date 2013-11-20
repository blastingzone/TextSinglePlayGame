// SUDGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameInput.h"
#include "Player.h"
#include "GameMap.h"
#include "GameMaster.h"
#include <crtdbg.h>
// �޸� ���� üũ
#ifdef _DEBUG
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	// �޸� ���� üũ
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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

	return 0;
}


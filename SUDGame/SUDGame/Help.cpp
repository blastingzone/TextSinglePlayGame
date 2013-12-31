#include "stdafx.h"
#include "Help.h"

CHelp* CHelp::m_pInstance = nullptr;

CHelp::CHelp(void)
{
}


CHelp::~CHelp(void)
{
}

CHelp* CHelp::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CHelp();
	}
	return m_pInstance;
}

void CHelp::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CHelp::printHelp()
{
	system("cls");

	printf("=============================================================\n\n");
	printf("도움말입니다\n");
	printf("도움말을 보는 도중에도 시간은 흐릅니다. 째깍째깍. \n\n");
	printf("10초가 지나면 체력이 5씩 회복됩니다. \n\n");
	printf("주인공은 화면에 골뱅이(@) 표시로 나타납니다. \n\n");
	printf("W S A D : 상 하 좌 우 이동\n");
	printf("F : Fury 모드 on / off \n");
	printf("Q : 게임 종료\n");
	printf("=============================================================\n");
	printf("게임의 목표는 크게 2가지 입니다.\n");
	printf("주인공은 어린 공주를 모시는 기사로, 손수 몬스터를 전멸시켜 섭정이 되거나\n");
	printf("몬스터를 죽여서 얻은 아이템으로 공주를 성장시킬 수 있습니다.\n");
	printf("아이템은 저마다의 효과가 있으며, 공주의 3대 능력치(힘, 민, 지)중 하나가 10이 넘으면 게임이 끝납니다.\n");
	printf("=============================================================\n");
	printf("공주가 있는 수도의 위치는 4,4입니다. 한 번 찾아가 보심이?\n");
	printf("=============================================================\n");

	printf("엔터 키를 누르세요\n");

	getchar();
}
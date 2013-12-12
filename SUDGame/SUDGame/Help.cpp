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
	printf("=========================\n");
	printf("도움말입니다\n");
	printf("W S A D : 상 하 좌 우 이동\n");
	printf("Q : 게임 종료\n");
	printf("아무 키나 누르세요\n");
	getchar();
}
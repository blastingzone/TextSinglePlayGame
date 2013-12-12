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
	printf("�����Դϴ�\n");
	printf("W S A D : �� �� �� �� �̵�\n");
	printf("Q : ���� ����\n");
	printf("�ƹ� Ű�� ��������\n");
	getchar();
}
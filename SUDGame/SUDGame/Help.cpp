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
	printf("�����Դϴ�\n");
	printf("������ ���� ���߿��� �ð��� �帨�ϴ�. °��°��. \n\n");
	printf("10�ʰ� ������ ü���� 5�� ȸ���˴ϴ�. \n\n");
	printf("���ΰ��� ȭ�鿡 �����(@) ǥ�÷� ��Ÿ���ϴ�. \n\n");
	printf("W S A D : �� �� �� �� �̵�\n");
	printf("F : Fury ��� on / off \n");
	printf("Q : ���� ����\n");
	printf("=============================================================\n");
	printf("������ ��ǥ�� ũ�� 2���� �Դϴ�.\n");
	printf("���ΰ��� � ���ָ� ��ô� ����, �ռ� ���͸� ������� ������ �ǰų�\n");
	printf("���͸� �׿��� ���� ���������� ���ָ� �����ų �� �ֽ��ϴ�.\n");
	printf("�������� �������� ȿ���� ������, ������ 3�� �ɷ�ġ(��, ��, ��)�� �ϳ��� 10�� ������ ������ �����ϴ�.\n");
	printf("=============================================================\n");
	printf("���ְ� �ִ� ������ ��ġ�� 4,4�Դϴ�. �� �� ã�ư� ������?\n");
	printf("=============================================================\n");

	printf("���� Ű�� ��������\n");

	getchar();
}
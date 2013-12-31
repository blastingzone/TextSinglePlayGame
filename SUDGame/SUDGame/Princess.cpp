#include "stdafx.h"
#include "Princess.h"

CPrincess* CPrincess::m_pInstance = nullptr;

CPrincess::CPrincess(void)
{
	m_Name = "����";

	// ����.
	m_CurrentPosition.i_Coordinate = 4;
	m_CurrentPosition.j_Coordinate = 4;

	m_HP = 5000;
	m_MP = 0;

	m_STR = 5;
	m_DEX = 5;
	m_INT = 5;

	m_affinityPoint = 0;
}


CPrincess::~CPrincess(void)
{
}


CPrincess* CPrincess::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CPrincess();
		return m_pInstance;
	}
	else
	{
		return m_pInstance;
	}
}

void CPrincess::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CPrincess::GetItemFromPlayer( ITEM_TYPE Item )
{
	switch( Item )
	{
	case MONSTER_BONE:
		++m_STR;
		printf_s("�� 1 ����!");
		break;
	case FLOWER_RING:
		++m_DEX;
		printf_s("��ø 1 ����!");
		break;
	case BLOOD:
		++m_INT;
		printf_s("���� 1 ����!");
		break;
	case GLASS_BOTTLE:
		++m_DEX;
		printf_s("��ø 1 ����!");
		break;
	case BROKEN_SILVER_SWORD:
		++m_STR;
		printf_s("�� 1 ����!");
		break;
	case POISONED_WINE:
		++m_INT;
		printf_s("���� 1 ����!");
		break;
	case ANCIENT_GOLD_COIN:
		++m_DEX;
		printf_s("��ø 1 ����!");
		break;
	case OLD_BOOK:
		++m_INT;
		printf_s("���� 1 ����!");
		break;
	}
	printf_s("���� �������� ����׿�. ������!\n");
}

#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster(void)
{
	// ���� �Ķ���� ���� (��� ���� ���� : ���� ����)
	m_HP = 125;
	m_MP = 15;
	m_STR = 9;
	m_DEX = 9;
	m_INT = 9;

	m_MonsterStatus = MONSTAT_NORMAL;
}


CMonster::~CMonster(void)
{
}

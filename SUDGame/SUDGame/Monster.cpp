#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster(void)
{
	// 기초 파라미터 설정 (모든 몬스터 동일 : 추후 수정)
	m_HP = 25;
	m_MP = 15;
	m_STR = 9;
	m_DEX = 9;
	m_INT = 9;
}


CMonster::~CMonster(void)
{
}

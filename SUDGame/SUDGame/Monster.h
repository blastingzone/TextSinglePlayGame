#pragma once
#include "character.h"
class CMonster :
	public CCharacter
{
public:
	CMonster(void);
	~CMonster(void);

private:
	// ������ �� ���� ��
	MONSTERSTATUS m_MonsterStatus;
};

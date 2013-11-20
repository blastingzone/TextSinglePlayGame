#pragma once
#include "character.h"
class CMonster :
	public CCharacter
{
public:
	CMonster(void);
	~CMonster(void);

private:
	// 아직은 안 쓰는 값
	MONSTERSTATUS m_MonsterStatus;
};


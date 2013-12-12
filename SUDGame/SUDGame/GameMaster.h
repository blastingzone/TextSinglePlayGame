#pragma once
#include "config.h"
#include "Monster.h"

struct Timer
{
	Timer() : m_PreviousCheckedTime(0.f), m_PresentCheckedTime(0.f) {}

	float m_PreviousCheckedTime;
	float m_PresentCheckedTime;
	float m_DifferentSecond;
};

class CGameMaster
{
public:
	CGameMaster(void);
	~CGameMaster(void);

	void CreateAndLocaleMonsters();

	void StartBattle(CMonster* mob);
	void CheckMob(Position position);
};


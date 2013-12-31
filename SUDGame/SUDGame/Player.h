#pragma once
#include "character.h"

class CPlayer :
	public CCharacter
{
public:
	CPlayer(void);
	~CPlayer(void);

	static CPlayer* GetInstance();
	void ReleaseInstance();

	void MovePlayer(DIRECTION DIR);

	void PrintPosition();
	void PrintStatusUI();

	//Player 전용 함수
	int GetHP()			{ return m_HP; }
	int GetMP()			{ return m_MP; }

	void RecoverStatus(int HPRecover, int MPRecover);

	void TurnFuryFlag()		{ SkillFuryFlag = !SkillFuryFlag; }
	bool GetFuryFlag()		{ return SkillFuryFlag; }

private:
	static CPlayer* m_pInstance;

	int m_MaxHP;
	int m_MaxMP;

	// 시간 한정 스킬용 플래그
	bool					SkillFuryFlag;
};


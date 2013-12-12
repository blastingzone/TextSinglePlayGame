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

private:
	static CPlayer* m_pInstance;
};


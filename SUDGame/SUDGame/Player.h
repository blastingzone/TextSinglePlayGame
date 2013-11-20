#pragma once
#include "character.h"

class CPlayer :
	public CCharacter
{
public:
	CPlayer(void);
	~CPlayer(void);

	static CPlayer* GetInstance();

	void MovePlayer(DIRECTION DIR);
	void PrintPosition();

private:
	static CPlayer* m_pInstance;
};


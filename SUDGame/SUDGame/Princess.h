#pragma once
#include "character.h"
class CPrincess :
	public CCharacter
{
public:
	CPrincess(void);
	virtual ~CPrincess(void);

	static CPrincess* GetInstance();
	void ReleaseInstance();

	void GetItemFromPlayer(ITEM_TYPE Item);

private:
	static CPrincess* m_pInstance;

	// ȣ����?
	int m_affinityPoint;
};


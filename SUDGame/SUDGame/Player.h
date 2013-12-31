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

	//Player ���� �Լ�
	int GetHP()			{ return m_HP; }
	int GetMP()			{ return m_MP; }

	void RecoverStatus(int HPRecover, int MPRecover);

	void TurnFuryFlag()		{ SkillFuryFlag = !SkillFuryFlag; }
	bool GetFuryFlag()		{ return SkillFuryFlag; }

	void GetItem(ITEM_TYPE Item);
	bool GiveItemToPrincess(ITEM_TYPE Item);
	void PrintItemList();

	char* GetItemName(ITEM_TYPE Item);

private:
	static CPlayer* m_pInstance;

	int m_MaxHP;
	int m_MaxMP;

	// �ð� ���� ��ų�� �÷���
	bool					SkillFuryFlag;

	// ���ΰ� ������ �迭 IDX = ������ ����, VALUE = ������ ����
	int						Inventory[ITEM_COUNT];
};

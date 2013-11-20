#include "stdafx.h"
#include "Character.h"


CCharacter::CCharacter(void)
{
}


CCharacter::~CCharacter(void)
{
}

void CCharacter::HitCheck(CCharacter* attacker)
{
	// �⺻ ���ݷ��� ���� 5��
	int defaultDamage = attacker->GetSTR() * 5;
	int hitCheck = (rand() % 20 + (attacker->GetDEX() - m_DEX));

	// ������ + ������ ��ø�� ������ 15 �ʰ��� ũ��Ƽ�� ��Ʈ
	if ( hitCheck > 15 )
	{
		m_HP -= defaultDamage * 2;
		printf_s("%s�� ũ��Ƽ�� ��Ʈ ���ߴ�! ������ (%d)�� �Ծ���! ���� ü�� %d \n",m_Name.c_str(), 2* defaultDamage, m_HP);
		return;
	}
	// ���� ���Ŀ��� 11 �̻� 15 ���ϸ� ��Ʈ
	else if ( hitCheck > 10 )
	{
		m_HP -= defaultDamage;
		printf_s("%s�� ���ݴ��ߴ�! ������ (%d)�� �Ծ���! ���� ü�� %d \n",m_Name.c_str(), defaultDamage, m_HP);
		return;
	}
	// ���� ���Ŀ��� 5 �̻� 10 ���ϸ� ���潺
	else if ( hitCheck > 4 )
	{
		m_HP -= defaultDamage / 2;
		printf_s("%s�� ����ߴ�! ������ (%d)�� �Ծ���! ���� ü�� %d \n",m_Name.c_str(), defaultDamage/2, m_HP);
		return;
	}
	// 4 ���ϸ� �̽�
	else
	{
		printf_s("%s�� ȸ���ߴ�! ���� ü�� %d \n",m_Name.c_str(), m_HP);
		return;
	}

}
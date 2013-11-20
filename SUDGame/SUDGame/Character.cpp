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
	// 기본 공격력은 힘의 5배
	int defaultDamage = attacker->GetSTR() * 5;
	int hitCheck = (rand() % 20 + (attacker->GetDEX() - m_DEX));

	// 랜덤값 + 공격자 민첩의 우위가 15 초과면 크리티컬 히트
	if ( hitCheck > 15 )
	{
		m_HP -= defaultDamage * 2;
		printf_s("%s은 크리티컬 히트 당했다! 데미지 (%d)를 입었다! 남은 체력 %d \n",m_Name.c_str(), 2* defaultDamage, m_HP);
		return;
	}
	// 같은 공식에서 11 이상 15 이하면 히트
	else if ( hitCheck > 10 )
	{
		m_HP -= defaultDamage;
		printf_s("%s은 공격당했다! 데미지 (%d)를 입었다! 남은 체력 %d \n",m_Name.c_str(), defaultDamage, m_HP);
		return;
	}
	// 같은 공식에서 5 이상 10 이하면 디펜스
	else if ( hitCheck > 4 )
	{
		m_HP -= defaultDamage / 2;
		printf_s("%s은 방어했다! 데미지 (%d)를 입었다! 남은 체력 %d \n",m_Name.c_str(), defaultDamage/2, m_HP);
		return;
	}
	// 4 이하면 미스
	else
	{
		printf_s("%s은 회피했다! 남은 체력 %d \n",m_Name.c_str(), m_HP);
		return;
	}

}
#include "stdafx.h"
#include "Player.h"

CPlayer* CPlayer::m_pInstance = nullptr;

CPlayer::CPlayer(void)
{
	// 시작 좌표 설정
	m_CurrentPosition.i_Coordinate = 0;
	m_CurrentPosition.j_Coordinate = 0;

	SetName("주인공");

	// 기초 파라미터 설정
	m_HP = 450;
	m_MaxHP = 450;
	m_MP = 150;
	m_MaxMP = 150;
	m_STR = 11;
	m_DEX = 11;
	m_INT = 11;

	// 스킬용 플래그 설정
	SkillFuryFlag = false;
}

CPlayer::~CPlayer(void)
{
}

CPlayer* CPlayer::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CPlayer();
		return m_pInstance;
	}
	else
	{
		return m_pInstance;
	}
}

// 이동하는 메소드
void CPlayer::MovePlayer(DIRECTION DIR)
{
	if (DIR == DIR_UP && (m_CurrentPosition.i_Coordinate > 0) )
	{
		--m_CurrentPosition.i_Coordinate;
	}

	if (DIR == DIR_DOWN && (m_CurrentPosition.i_Coordinate < WORLD_MAP_HEIGHT-1) )
	{
		++m_CurrentPosition.i_Coordinate;
	}

	if (DIR == DIR_LEFT && (m_CurrentPosition.j_Coordinate > 0))
	{
		--m_CurrentPosition.j_Coordinate;
	}

	if (DIR == DIR_RIGHT && (m_CurrentPosition.j_Coordinate < WORLD_MAP_WIDTH-1) )
	{
		++m_CurrentPosition.j_Coordinate;
	}
}

void CPlayer::PrintPosition()
{
	printf_s("현재 위치는 : %d, %d 입니다. \n", m_CurrentPosition.i_Coordinate, m_CurrentPosition.j_Coordinate);
}

void CPlayer::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CPlayer::PrintStatusUI()
{
	printf("\n");
	printf("+~=~=~ %5s STATUS =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=+\n", m_Name.c_str());
	printf("|   체력 : %5d     마력 : %5d                   |\n", m_HP, m_MP );
	printf("|   근력 : %5d     민첩 : %5d    지능 : %5d   |\n", m_STR, m_DEX, m_INT );
	printf("+~=~=~=~=~=~=~~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=+\n");
}

void CPlayer::RecoverStatus( int HPRecover, int MPRecover )
{
	m_HP += HPRecover;
	
	if (m_HP > m_MaxHP)
	{
		m_HP = m_MaxHP;
	}

	m_MP += MPRecover;

	if (m_MP > m_MaxMP)
	{
		m_MP = m_MaxMP;
	}

	printf_s("체력 변화 %3d, 마나 변화 %3d \n", HPRecover, MPRecover);
}

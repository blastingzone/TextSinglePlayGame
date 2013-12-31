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

	// 생성될 때는 모든 아이템이 0개
	for (int i = 0 ; i < ITEM_COUNT ; ++i)
	{
		Inventory[i] = 0;
	}
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

bool CPlayer::GiveItemToPrincess( ITEM_TYPE Item )
{
	// 보유한 아이템이 1 이상일 때만 줄 수 있다.
	if (Inventory[Item] > 0)
	{
		--Inventory[Item];
		return true;
	}
	else
	{
		printf_s("...아무것도 없는데요?\n");
		return false;
	}
}

void CPlayer::GetItem( ITEM_TYPE Item )
{
	if ( Item < ITEM_COUNT )
	{
		Inventory[Item]++;
		printf_s("아이템을 얻었다! : %s\n", GetItemName(Item));
	}
}

void CPlayer::PrintItemList()
{
	printf_s("\n===========인벤토리==========\n");
	for (int i = 0; i < ITEM_COUNT; ++i)
	{
		ITEM_TYPE tempItemType = static_cast<ITEM_TYPE>(i);
		printf_s("%d. %s : %d 개\n", i, GetItemName( tempItemType ), Inventory[tempItemType]);
	}
	printf_s("\n===========================\n");
	printf_s("공주에게 줄 수 있는 아이템들입니다. 엔터 키를 누르세요.\n");
	getchar();
}

// 아이템 타입을 주면 이름이 나오는 함수
char* CPlayer::GetItemName(ITEM_TYPE Item)
{
	switch( Item )
	{
	case MONSTER_BONE:
		return "몬스터 뼈";
	case FLOWER_RING:
		return "꽃반지";
	case BLOOD:
		return "정체불명의 괴물 피";
	case GLASS_BOTTLE:
		return "유리병";
	case BROKEN_SILVER_SWORD:
		return "부서진 은장도";
	case POISONED_WINE:
		return "독약이 든 와인";
	case ANCIENT_GOLD_COIN:
		return "고대의 황금 주화";
	case OLD_BOOK:
		return "낡은 책";
	}
	return "아이템이 아닙니다.";
}
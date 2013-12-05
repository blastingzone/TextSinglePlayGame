#include "stdafx.h"
#include "GameMap.h"

CGameMap* CGameMap::m_pInstance = nullptr;

CGameMap::CGameMap(void)
{
}


CGameMap::~CGameMap(void)
{
	DeleteAllMonster();
}

CGameMap* CGameMap::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CGameMap();
		return m_pInstance;
	}
	else
	{
		return m_pInstance;
	}
}

CMapTile* CGameMap::GetMapType(Position currentPosition) 
{
	return &m_WorldGameMap[currentPosition.i_Coordinate][currentPosition.j_Coordinate];
}

void CGameMap::InitMap()
{
	SetRandomTileTypeAllMap();
}

void CGameMap::PrintMap()
{
	printf_s(" ::::::::: 세계지도   ~ : 강, ^ : 산, D : 던전, T : 마을 ::::::::::\n\n ");
	for (int i = 0; i < WORLD_MAP_HEIGHT-1 ; i++)
	{
		for (int j = 0; j < WORLD_MAP_WIDTH-1 ; j++)
		{
			switch(GetMapType(Position(i, j))->GetTileType())
			{
			case TYPE_MOUNTAIN:
				printf_s(" ^ ");
				break;
			case TYPE_DUNGEON:
				printf_s(" D ");
				break;
			case TYPE_RIVER:
				printf_s(" ~ ");
				break;
			case TYPE_ROAD:
				printf_s("   ");
				break;
			case TYPE_TOWN:
				printf_s(" T ");
				break;
			}
		}
		printf_s("\n");
	}
}

// agebreak : 현재 버전에는 맵이 랜덤으로 생성되어서, 시작해서 움직이지 못하는 경우가 생기는 버그가 있습니다. 
// 최종 버전에는 이런 버그들도 해결되길 바랍니다. ^^
// 그리고 캐릭터가 맵에 표시되지 않아서, 확인이 어려운 점도 있습니다. 
void CGameMap::SetRandomTileTypeAllMap()
{
	int randomValue;
	for (int i = 0; i < WORLD_MAP_HEIGHT-1 ; i++)
	{
		for (int j = 0; j < WORLD_MAP_WIDTH-1 ; j++)
		{
			randomValue = rand() % sizeof(TILE_TYPE);
			// 예전 리뷰 : C++에서 형변환은 반대로 해야 합니다. (오히려 아래와 같은 형태로 되는게 신기.. ㅡ.ㅡ;;)
			// --> 헐 그럴수가
			//m_WorldGameMap[i][j].SetTileType(TILE_TYPE(randomValue) );
			m_WorldGameMap[i][j].SetTileType(static_cast<TILE_TYPE>(randomValue) );
		}
	}
}

void CGameMap::SetMonster(int i, int j, CMonster* mob)
{
	m_WorldGameMap[i][j].SetMonster(mob);
}

bool CGameMap::IsMovableCoordinate(Position position, DIRECTION DIR)
{
	switch(DIR)
	{
	case DIR_DOWN:
		++position.i_Coordinate;
		break;
	case DIR_UP:
		--position.i_Coordinate;
		break;
	case DIR_LEFT:
		--position.j_Coordinate;
		break;
	case DIR_RIGHT:
		++position.j_Coordinate;
		break;
	}

	// agebreak : 굳이 같은 클래스내에서는 싱글톤 클래스를 사용할 필요가 없습니다. 
	//return CGameMap::GetInstance()->GetMapType(position)->IsMovable();
	return GetMapType(position)->IsMovable();
}

void CGameMap::DeleteAllMonster()
{
	for (int i = 0; i < WORLD_MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < WORLD_MAP_WIDTH; ++j)
		{
			m_WorldGameMap[i][j].DeleteMonster();
		}
	}
}

void CGameMap::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
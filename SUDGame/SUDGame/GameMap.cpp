#include "stdafx.h"
#include "GameMap.h"

CGameMap* CGameMap::m_pInstance = nullptr;

CGameMap::CGameMap(void)
{
}


CGameMap::~CGameMap(void)
{
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

void CGameMap::SetRandomTileTypeAllMap()
{
	int randomValue;
	for (int i = 0; i < WORLD_MAP_HEIGHT-1 ; i++)
	{
		for (int j = 0; j < WORLD_MAP_WIDTH-1 ; j++)
		{
			randomValue = rand() % sizeof(TILE_TYPE);
			m_WorldGameMap[i][j].SetTileType(TILE_TYPE(randomValue) );
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
	return CGameMap::GetInstance()->GetMapType(position)->IsMovable();
}
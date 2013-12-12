#include "stdafx.h"
#include "MapTile.h"


CMapTile::CMapTile(void)
{
	SetDescription("타일 설명 임시 테스트");
	m_Monster = nullptr;
}

CMapTile::~CMapTile(void)
{
}

void CMapTile::Render()
{
	if (!m_Description.empty())
	{
		printf_s("%s\n", m_Description.c_str());
	}
}

void CMapTile::SetDescription(const std::string& description)
{
	m_Description = description;
}

void CMapTile::SetTileType(TILE_TYPE type)
{
	switch(type)
	{
	case TYPE_DUNGEON:
		m_Movable = true;
		break;
	case TYPE_MOUNTAIN:
		m_Movable = false;
		break;
	case TYPE_RIVER:
		m_Movable = false;
		break;
	case TYPE_ROAD:
		m_Movable = true;
		break;
	case TYPE_TOWN:
		m_Movable = true;
		break;
	}
	m_TileType = type;
}

void CMapTile::SetMonster(CMonster* mob)
{
	DeleteMonster();

	m_Monster = mob;
}

void CMapTile::DeleteMonster()
{
	if (nullptr != m_Monster)
	{
		delete m_Monster;
		m_Monster = nullptr;
	}
}
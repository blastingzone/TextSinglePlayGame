#pragma once
#include "Monster.h"
#include <string>

class CMapTile
{
public:
	CMapTile(void);
	~CMapTile(void);

	void Render();
	void SetDescription(std::string description);
	
	TILE_TYPE	GetTileType() {return m_TileType;}
	void SetTileType(TILE_TYPE type);

	CMonster* GetMonster() {return m_Monster;}
	void SetMonster(CMonster* mob);

	void DeleteMonster();

	bool IsMovable() {return m_Movable;}

private:
	std::string		m_Description;

	char			m_TileName[32];
	bool			m_Movable;
	CMonster*		m_Monster;
	TILE_TYPE		m_TileType;
};


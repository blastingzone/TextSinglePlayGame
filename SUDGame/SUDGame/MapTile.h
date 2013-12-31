#pragma once
#include "Monster.h"
#include <string>

class CMapTile
{
public:
	CMapTile(void);
	~CMapTile(void);

	void Render();
	// 맵 타일의 설명을 입력함
	void SetDescription(const std::string& description);
	
	// 타일 타입 Set & Get
	TILE_TYPE	GetTileType()				{ return m_TileType; }
	void SetTileType(TILE_TYPE type);

	// 몬스터 Set & Get
	CMonster* GetMonster()					{ return m_Monster; }
	void SetMonster(CMonster* mob);

	void DeleteMonster();

	// 타일이 이동 가능한지 아닌지 알려줌
	bool IsMovable()						{ return m_Movable; }

private:
	std::string		m_Description;

	char			m_TileName[32];
	bool			m_Movable;
	CMonster*		m_Monster;
	TILE_TYPE		m_TileType;
};


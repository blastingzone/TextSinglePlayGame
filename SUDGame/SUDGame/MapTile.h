#pragma once
#include "Monster.h"
#include <string>

class CMapTile
{
public:
	CMapTile(void);
	~CMapTile(void);

	void Render();
	// �� Ÿ���� ������ �Է���
	void SetDescription(const std::string& description);
	
	// Ÿ�� Ÿ�� Set & Get
	TILE_TYPE	GetTileType()				{ return m_TileType; }
	void SetTileType(TILE_TYPE type);

	// ���� Set & Get
	CMonster* GetMonster()					{ return m_Monster; }
	void SetMonster(CMonster* mob);

	void DeleteMonster();

	// Ÿ���� �̵� �������� �ƴ��� �˷���
	bool IsMovable()						{ return m_Movable; }

private:
	std::string		m_Description;

	char			m_TileName[32];
	bool			m_Movable;
	CMonster*		m_Monster;
	TILE_TYPE		m_TileType;
};


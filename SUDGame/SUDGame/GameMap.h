#pragma once
#include "MapTile.h"

class CGameMap
{
public:
	CGameMap(void);
	~CGameMap(void);

	static CGameMap* GetInstance();

	void InitMap();
	CMapTile* GetMapType(Position currentPosition);
	void PrintMap();

	void SetRandomTileTypeAllMap();
	void SetMonster(int i, int j, CMonster* mob);
	bool IsMovableCoordinate(Position position, DIRECTION DIR);

private:
	CMapTile m_WorldGameMap[WORLD_MAP_WIDTH][WORLD_MAP_HEIGHT];
	static CGameMap* m_pInstance;
};

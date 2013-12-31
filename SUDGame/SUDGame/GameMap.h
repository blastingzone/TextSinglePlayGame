#pragma once
#include "MapTile.h"

class CGameMap
{
public:
	CGameMap(void);
	~CGameMap(void);

	static CGameMap* GetInstance();

	void		InitMap();
	CMapTile*	GetMapType(Position currentPosition);
	
	void		PrintMap();
	void		PrintFurySkillMap();

	// 얘는 이제 테스트 함수가 되었습니다.
	void		SetRandomTileTypeAllMap();

	// 실제로 맵을 생성하는 메소드
	void		CreateAllMapByFile();
	std::string GameMapParserByPosition(int RowOrColNum);
	TILE_TYPE	StringToTileType(std::string string);

	void		SetMonster(int i, int j, CMonster* mob);
	bool		IsMovableCoordinate(Position position, DIRECTION DIR);

	void		DeleteAllMonster();
	void		ReleaseInstance();
	
private:
	CMapTile			m_WorldGameMap[WORLD_MAP_WIDTH][WORLD_MAP_HEIGHT];
	static CGameMap*	m_pInstance;
};

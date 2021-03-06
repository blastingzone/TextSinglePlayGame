#pragma once
// 월드맵 크기
const int WORLD_MAP_WIDTH = 10;
const int WORLD_MAP_HEIGHT = 10;

// 좌표 구조체
struct Position
{
	Position() {};
	Position(int i, int j) {i_Coordinate = i; j_Coordinate = j;}

	int i_Coordinate;
	int j_Coordinate;
};

// 이동 방향
enum DIRECTION
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
};

// 게임 상태값
enum GAMESTATUS
{
	STAT_WORLD_MAP_MOVE,
	STAT_IN_TILE,
	STAT_BATTLE
};

// 몬스터 상태값
enum MONSTERSTATUS
{
	MONSTAT_NORMAL,
	MONSTAT_FURY,
	MONSTAT_BERSERK,
	MONSTAT_WEAKEN
};

// 지형 타입
enum TILE_TYPE
{
	TYPE_MOUNTAIN,
	TYPE_RIVER,
	TYPE_TOWN,
	TYPE_DUNGEON,
	TYPE_ROAD,
	TYPE_COUNT
};

// 엔딩 타입
enum ENDING_TYPE
{
	CONTINUE_GAME,
	ENDING_MONSTER_ELIMINATION,
	ENDING_PRINCESS_DOMINATE,
};

// 몬스터 종류
static const char* MOBNAME[5]  = {"좀비", "드래곤", "스켈레톤", "악마"};

// 드랍되는 아이템 종류
enum ITEM_TYPE
{
	MONSTER_BONE,
	FLOWER_RING,
	BLOOD,
	GLASS_BOTTLE,
	BROKEN_SILVER_SWORD,
	POISONED_WINE,
	ANCIENT_GOLD_COIN,
	OLD_BOOK,
	ITEM_COUNT,
};
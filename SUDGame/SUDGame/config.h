#pragma once
// ����� ũ��
const int WORLD_MAP_WIDTH = 10;
const int WORLD_MAP_HEIGHT = 10;

// ��ǥ ����ü
struct Position
{
	Position() {};
	Position(int i, int j) {i_Coordinate = i; j_Coordinate = j;}

	int i_Coordinate;
	int j_Coordinate;
};

// �̵� ����
enum DIRECTION
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
};

// ���� ���°�
enum GAMESTATUS
{
	STAT_WORLD_MAP_MOVE,
	STAT_IN_TILE,
	STAT_BATTLE
};

// ���� ���°�
enum MONSTERSTATUS
{
	MONSTAT_NORMAL,
	MONSTAT_FURY,
	MONSTAT_BERSERK,
	MONSTAT_WEAKEN
};

// ���� Ÿ��
enum TILE_TYPE
{
	TYPE_MOUNTAIN,
	TYPE_RIVER,
	TYPE_TOWN,
	TYPE_DUNGEON,
	TYPE_ROAD,
	TYPE_COUNT
};

// ���� Ÿ��
enum ENDING_TYPE
{
	CONTINUE_GAME,
	ENDING_MONSTER_ELIMINATION,
};

// ���� ����
static const char* MOBNAME[5]  = {"����", "�巡��", "���̷���", "�Ǹ�"};
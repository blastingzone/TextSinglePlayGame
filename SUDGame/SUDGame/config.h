#pragma once
// ����� ũ��
const int WORLD_MAP_WIDTH = 10;
const int WORLD_MAP_HEIGHT = 10;

// ��ǥ ����ü
struct Position
{
	Position() {};
	Position(int i, int j) {x_Coordinate = i; y_Coordinate = j;}

	int x_Coordinate;
	int y_Coordinate;
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
	TYPE_ROAD
};

// ���� ����
static const char* MOBNAME[5]  = {"����", "�巡��", "���̷���", "�Ǹ�"};
#include "stdafx.h"
#include "GameMap.h"
#include "tinyXML/tinyxml.h"
#include "tinyXML/xpath_static.h"
#include "Player.h"

CGameMap* CGameMap::m_pInstance = nullptr;

CGameMap::CGameMap(void)
{
}


CGameMap::~CGameMap(void)
{
	DeleteAllMonster();
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

// 맵 초기화에는 맵을 XML에서 로드하는 부분도 들어있다.
void CGameMap::InitMap()
{
	// 테스트용 랜덤 맵 (실제 구현시 주석)
	// SetRandomTileTypeAllMap();

	// XML 출력 테스트용
	std::string filePath = "";
	filePath.append("./XmlData/GameMap.xml");

	TiXmlDocument gameMapData = TiXmlDocument( filePath.c_str() );

	CreateAllMapByFile();
}

void CGameMap::PrintMap()
{
	printf_s(" ::::::::: 세계지도   ~ : 강, ^ : 산, D : 던전, T : 마을 ::::::::::\n\n");
	for (int i = 0; i < WORLD_MAP_HEIGHT ; i++)
	{
		for (int j = 0; j < WORLD_MAP_WIDTH ; j++)
		{
			Position PlayerPosition = CPlayer::GetInstance()->GetPosition();
			if (PlayerPosition.i_Coordinate == i 
				&& PlayerPosition.j_Coordinate == j)
			{
				printf_s(" @ ");
			}
			else
			{
				switch( GetMapType( Position(i, j) )->GetTileType() )
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
		}
		printf_s("\n");
	}
}

// Fury 스킬을 쓰면 몹 위치가 보인다.
void CGameMap::PrintFurySkillMap()
{
	printf_s(" ::::::::: Fury Mode! Fury Mode! Fury Mode! ::::::::::\n\n");
	for (int i = 0; i < WORLD_MAP_HEIGHT ; i++)
	{
		for (int j = 0; j < WORLD_MAP_WIDTH ; j++)
		{
			Position PlayerPosition = CPlayer::GetInstance()->GetPosition();
			if (PlayerPosition.i_Coordinate == i 
				&& PlayerPosition.j_Coordinate == j)
			{
				printf_s(" @ ");
			}
			else
			{
				if ( GetMapType( Position(i, j) )->GetMonster() )
				{
					printf_s(" M ");
				}
				else
				{
					printf_s("   ");
				}
			}
		}
		printf_s("\n");
	}
}

// agebreak : 현재 버전에는 맵이 랜덤으로 생성되어서, 시작해서 움직이지 못하는 경우가 생기는 버그가 있습니다. 
// 최종 버전에는 이런 버그들도 해결되길 바랍니다. ^^
// 그리고 캐릭터가 맵에 표시되지 않아서, 확인이 어려운 점도 있습니다. 
// 넵 ^^;;
void CGameMap::SetRandomTileTypeAllMap()
{
	int randomValue;
	for (int i = 0; i < WORLD_MAP_HEIGHT-1 ; i++)
	{
		for (int j = 0; j < WORLD_MAP_WIDTH-1 ; j++)
		{
			randomValue = rand() % TYPE_COUNT;
			// 예전 리뷰 : C++에서 형변환은 반대로 해야 합니다. (오히려 아래와 같은 형태로 되는게 신기.. ㅡ.ㅡ;;)
			// --> 헐 그럴수가
			//m_WorldGameMap[i][j].SetTileType(TILE_TYPE(randomValue) );
			m_WorldGameMap[i][j].SetTileType( static_cast<TILE_TYPE>(randomValue) );
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

	// 굳이 같은 클래스내에서는 싱글톤 클래스를 사용할 필요가 없습니다. 
	//return CGameMap::GetInstance()->GetMapType(position)->IsMovable();
	// Aㅏ;
	return GetMapType(position)->IsMovable();
}

void CGameMap::DeleteAllMonster()
{
	for (int i = 0; i < WORLD_MAP_HEIGHT; ++i)
	{
		for (int j = 0; j < WORLD_MAP_WIDTH; ++j)
		{
			m_WorldGameMap[i][j].DeleteMonster();
		}
	}
}

void CGameMap::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void CGameMap::CreateAllMapByFile()
{
	// 경로 설정
	std::string filePath = "";
	filePath.append("./XmlData/GameMap.xml");

	TiXmlDocument gameMapData = TiXmlDocument( filePath.c_str() );

	// xml 파일에서 데이터를 불러온다.
	bool isLoaded = gameMapData.LoadFile();
	if ( !isLoaded )
	{
		printf_s("XML 불러오기에 문제가 생겼습니다.\n");
		getchar();
		return;
	}

	TiXmlElement* pRoot = gameMapData.FirstChildElement("Map");
	printf_s("%s\n", (char*)(pRoot->FirstChildElement("Description")->GetText()) );

	// xml에 접근하기 위한 문자열들
	std::string row;
	std::string col;

	// 모든 좌표를 순회하면서 해당 좌표에 대한 XML 정보가 있는지 확인한다.
	// 있으면 타일 설정을 해당 좌표에 따라 맞춘다.
	// 없으면 타일을 기본 설정으로 맞춘다.

	TiXmlNode* targetNode = nullptr;
	TiXmlElement* targetElement = nullptr;

	for (int i = 0; i < WORLD_MAP_HEIGHT; ++i)
	{
		row = GameMapParserByPosition(i);
		// 행을 불러온다.
		targetNode = pRoot->FirstChildElement(row.c_str());

		for (int j = 0; j < WORLD_MAP_WIDTH; ++j)
		{
			col = GameMapParserByPosition(j);

			// 행을 불러오는데 성공하면 내부의 열을 불러온다.
			// 이렇게 안 하면 에러난다!
			if ( targetNode )
			{
				targetElement = targetNode->FirstChildElement(col.c_str());
			}
			// 열을 불러오는데도 성공했으면 맵의 설명과 타일을 받아서 맵을 생성한다.
			// 이렇게 안 하면 에러난다!
			if ( targetElement )
			{
				// XML로 받아온 Tile_Type을 맵 속성으로 할당한다.
				TILE_TYPE tileType = static_cast<TILE_TYPE>( StringToTileType( targetElement->FirstChildElement("TileType")->GetText() ) );

				m_WorldGameMap[i][j].SetTileType( tileType );

				// XML로 받아온 Description을 맵 속성으로 할당한다.
				const char* description = targetElement->FirstChildElement("Description")->GetText();

				m_WorldGameMap[i][j].SetDescription( description );
			}
			// targetElement가 nullptr인 경우는 XML에 해당 자료가 없는 것이다.
			// 이 때는 디폴트 값으로 TILE_TYPE을 길로 바꾼 맵을 넣어준다.
			else
			{
				m_WorldGameMap[i][j].SetTileType(TYPE_ROAD);
				m_WorldGameMap[i][j].SetDescription( "평범한 길이다." );
			}
		}
	}
	printf_s("Map 불러오기 성공! 엔터 키를 누르세요 \n");
	getchar();
}

std::string CGameMap::GameMapParserByPosition(int RowOrColNum)
{
	std::string rowOrCol;

	// 이 항목들은 XML 문서와 맞춰야 맵 불러오기에 문제가 없습니다.
	switch(RowOrColNum)
	{
	case 0:
		rowOrCol = "Zero";
		break;
	case 1:
		rowOrCol = "One";
		break;
	case 2:
		rowOrCol = "Two";
		break;
	case 3:
		rowOrCol = "Three";
		break;
	case 4:
		rowOrCol = "Four";
		break;
	case 5:
		rowOrCol = "Five";
		break;
	case 6:
		rowOrCol = "Six";
		break;
	case 7:
		rowOrCol = "Seven";
		break;
	case 8:
		rowOrCol = "Eight";
		break;
	case 9:
		rowOrCol = "Nine";
		break;
	default:
		rowOrCol = "Err";
		break;
	}

	if ( !strcmp("Err", rowOrCol.c_str()) )
	{
		printf_s("좌표 - 글자 변환 에러! 게임을 종료해 주세요. \n");
		getchar();

		return NULL;
	}

	return rowOrCol;
}

TILE_TYPE CGameMap::StringToTileType(std::string string)
{
	if ( !strcmp("TYPE_DUNGEON",string.c_str()) )
		return TYPE_DUNGEON;

	if ( !strcmp("TYPE_MOUNTAIN",string.c_str()) )
		return TYPE_MOUNTAIN;

	if ( !strcmp("TYPE_RIVER",string.c_str()) )
		return TYPE_RIVER;

	if ( !strcmp("TYPE_ROAD",string.c_str()) )
		return TYPE_ROAD;

	if ( !strcmp("TYPE_TOWN",string.c_str()) )
		return TYPE_TOWN;

	// 이거 리턴하면 뭔가 잘못된거다.
	return TYPE_COUNT;
}
#include "stdafx.h"
#include "GameMaster.h"
#include "GameMap.h"
#include "Player.h"
#include <random>


CGameMaster::CGameMaster(void)
{
}


CGameMaster::~CGameMaster(void)
{
}

void CGameMaster::CreateAndLocaleMonsters()
{
	int random_x;
	int random_y;
	int i = 0;
	char buf[32];

	while ( i < ((WORLD_MAP_HEIGHT * WORLD_MAP_WIDTH) >> 2))
	{
		random_x = rand() % WORLD_MAP_HEIGHT;
		random_y = rand() % WORLD_MAP_WIDTH;

		if (NULL == CGameMap::GetInstance()->GetMapType( Position(random_x, random_y) )->GetMonster())
		{
			CMonster* pMob = new CMonster();

			sprintf_s(buf, "%s %d", MOBNAME[i % 4], i);
			std::string szName = buf;

			pMob->SetName(szName);

			pMob->SetPosition(random_x, random_y);
			CGameMap::GetInstance()->SetMonster(random_x, random_y, pMob);

			printf_s("몹 이름 : %s 몹 위치 : %d, %d \n", pMob->GetName().c_str(), pMob->GetPosition().i_Coordinate, pMob->GetPosition().j_Coordinate);
			
			++i;
		}
	}
	printf_s("맵 크기 : %d, 몹 수량 : %d 배치되었습니다! \n", WORLD_MAP_HEIGHT* WORLD_MAP_WIDTH, i);
}


void CGameMaster::StartBattle(CMonster* mob)
{
	int battleCounter = 0;
	printf_s("===================Battle Start!!====================\n");
	while (CPlayer::GetInstance()->IsAlive() && mob->IsAlive() )
	{
		if (battleCounter % 2)
		{
			mob->HitCheck(CPlayer::GetInstance());
		}
		else
		{
			CPlayer::GetInstance()->HitCheck(mob);	
		}
		++battleCounter;
		Sleep(1000);
	}
	printf_s("===================Battle END!!====================\n");
	// 유저가 이기면 타일의 몹을 삭제하고 몹 자리를 nullptr로 바꾼다
	if (CPlayer::GetInstance()->IsAlive())
	{
		// SetMonster에 Delete가 포함되어 있다
		CGameMap::GetInstance()->GetMapType(CPlayer::GetInstance()->GetPosition())
			->SetMonster(nullptr);
	}
	// 유저가 죽으면 게임을 끝낸다
	else
	{
		printf_s("You Are Dead...\n");
		getchar();
		exit(0);
	}
	getchar();
}

void CGameMaster::CheckMob(Position position)
{
	CMonster* Mob = CGameMap::GetInstance()->GetMapType(position)->GetMonster();
	if (Mob)
	{
		StartBattle(Mob);
	}
}

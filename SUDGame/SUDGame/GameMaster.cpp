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

			printf_s("�� �̸� : %s �� ��ġ : %d, %d \n", pMob->GetName().c_str(), pMob->GetPosition().i_Coordinate, pMob->GetPosition().j_Coordinate);
			
			++i;
		}
	}
	printf_s("�� ũ�� : %d, �� ���� : %d ��ġ�Ǿ����ϴ�! \n", WORLD_MAP_HEIGHT* WORLD_MAP_WIDTH, i);
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
	// ������ �̱�� Ÿ���� ���� �����ϰ� �� �ڸ��� nullptr�� �ٲ۴�
	if (CPlayer::GetInstance()->IsAlive())
	{
		// SetMonster�� Delete�� ���ԵǾ� �ִ�
		CGameMap::GetInstance()->GetMapType(CPlayer::GetInstance()->GetPosition())
			->SetMonster(nullptr);
	}
	// ������ ������ ������ ������
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

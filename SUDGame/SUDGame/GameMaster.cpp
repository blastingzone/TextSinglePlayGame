#include "stdafx.h"
#include "GameMaster.h"
#include "GameMap.h"
#include "Player.h"
#include <random>
#include "Timer.h"


CGameMaster::CGameMaster(void)
{
}


CGameMaster::~CGameMaster(void)
{
}

//�������� ���͸� �����ؼ� �� ������ �ѷ��ִ� �Լ�
void CGameMaster::CreateAndLocaleMonsters()
{
	int random_x;
	int random_y;
	int i = 0;
	char buf[32];

	// ��ü ���� 50%�� ���� ����
	// while ( i < ((WORLD_MAP_HEIGHT * WORLD_MAP_WIDTH) >> 2))
	// �׽�Ʈ�� : ���� 1������ ��
	while ( i < 1 )
	{
		random_x = rand() % WORLD_MAP_HEIGHT;
		random_y = rand() % WORLD_MAP_WIDTH;

		// ���Ͱ� �̵� ������ �������� �Ҵ�ǵ��� ����
		if (NULL == CGameMap::GetInstance()->GetMapType( Position(random_x, random_y) )->GetMonster()
			&& CGameMap::GetInstance()->GetMapType( Position(random_x, random_y) )->IsMovable())
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
	// Ÿ�̸Ӹ� �����.
	CTimer::DoTimerStop();

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
		Sleep(1500);
	}
	printf_s("=========================Battle END!!=========================\n");
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
	printf_s("���� ����! \n �ƹ� Ű�� ��������!");
	getchar();
	// ������� �����ϸ� ���� �����̹Ƿ� Ÿ�̸Ӹ� �ٽ� �����Ѵ�
	CTimer::DoTimerGo();
}

void CGameMaster::CheckMob(Position position)
{
	CMonster* Mob = CGameMap::GetInstance()->GetMapType(position)->GetMonster();
	if (Mob)
	{
		StartBattle(Mob);
	}
}

// ���� ���� ������ �˻��Ѵ�.
ENDING_TYPE CGameMaster::GameEndCheck()
{
	// ���� ���� 1 : ��� ���� ����
	int IsRestMonsterNum = 0;

	for ( int i = 0; i < WORLD_MAP_HEIGHT; ++i )
	{
		for ( int j = 0; j < WORLD_MAP_WIDTH; ++j )
		{
			// ��� Ÿ���� ���鼭 ���Ͱ� �ִ��� �˻�
			if ( CGameMap::GetInstance()->GetMapType( Position(i, j) )->GetMonster() )
			{
				++IsRestMonsterNum;
			}
		}
	}

	// ���� ���Ͱ� �ϳ��� ���ٸ�?
	if ( IsRestMonsterNum == 0 )
	{
		return ENDING_MONSTER_ELIMINATION;
	}

	// ���� ���ǿ� �ش���� ������
	return CONTINUE_GAME;
}

void CGameMaster::EndingScene( ENDING_TYPE Ending )
{
	switch(Ending)
	{
	case ENDING_MONSTER_ELIMINATION:
		printf_s("����� ��� ���͸� ������״�. ����� ����� ���� ������ �������� �̸��� ���� ���̴�... \n");
		getchar();
		break;
	// �� ��� q�� ���� ���� ���ῡ �ش�. �׳� �ѱ��.
	case CONTINUE_GAME:
		break;
	}
}

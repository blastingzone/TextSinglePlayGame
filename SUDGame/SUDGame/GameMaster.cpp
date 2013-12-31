#include "stdafx.h"
#include "GameMaster.h"
#include "GameMap.h"
#include "Player.h"
#include <random>
#include "Timer.h"
#include "Princess.h"


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
	//while ( i < 1 )
	while ( i < ((WORLD_MAP_HEIGHT * WORLD_MAP_WIDTH) >> 2))
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

		// ���� �¸��� ���� �������� ��� �Ǵ� ��� �߰�.
		ITEM_TYPE RandomItem = static_cast<ITEM_TYPE>( rand() % ITEM_COUNT );

		CPlayer::GetInstance()->GetItem(RandomItem);
	}
	// ������ ������ ������ ������
	else
	{
		printf_s("You Are Dead...\n");
		getchar();
		exit(0);
	}
	printf_s("���� ����! \n ���� Ű�� ��������!");
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

	// �������� 2 : ������ �ɷ�ġ �� �ϳ��� 10�� �Ѵ´�.
	int PrincessInt = CPrincess::GetInstance()->GetINT();
	int PrincessStr = CPrincess::GetInstance()->GetSTR();
	int PrincessDex = CPrincess::GetInstance()->GetDEX();

	if (PrincessInt > 10 || PrincessDex > 10 || PrincessStr > 10)
		return ENDING_PRINCESS_DOMINATE;

	// ���� ���ǿ� �ش���� ������
	return CONTINUE_GAME;
}

void CGameMaster::EndingScene( ENDING_TYPE Ending )
{
	system("cls");

	// ����
	printf_s("i.:::::::,,.,.,.,.,.,........ ....:riPi\n");
	printf_s(": ......                          .ri. r\n");
	printf_s(":.:,:,,.,.,.,.......... ... .   .:rir0@M\n");
	printf_s(":.,,,:,,.,........   . . .    .rU0G@Bq. \n");
	printf_s(": ,.,.,...... .            :vSZP27:     \n");
	printf_s(". ........ . .        ,i7JYLi.          \n");
	printf_s(". ......... . .   .;YL7:.               \n");
	printf_s(". ...... . .    iqSr                    \n");
	printf_s(". .........   7BB:                      \n");
	printf_s(":.::,:::...  @BL                        \n");
	printf_s(". :,,..  .  @Bi                         \n");
	printf_s(". :,,.. i. @B2         ENDING           \n");
	printf_s(":      :. ,@X:                          \n");

	switch(Ending)
	{
	case ENDING_MONSTER_ELIMINATION:
		printf_s("\n����� ��� ���͸� ������״�.\n ����� ����� ���� ������ �������� �̸��� ���� ���̴�... \n");
		getchar();
		break;
	case ENDING_PRINCESS_DOMINATE:
		printf_s("\n����� ���ָ� �Ǹ��� Ű���½��ϴ�.\n ���� ������ ���ֿ��� �ðܵ� �ǰ���... \n");
	// �� ��� q�� ���� ���� ���ῡ �ش�. �׳� �ѱ��.
	case CONTINUE_GAME:
		break;
	}
	printf_s("\n\n �����մϴ�! ���� ���Դϴ�. \n");
	getchar();
}

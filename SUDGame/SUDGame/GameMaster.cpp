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

//랜덤으로 몬스터를 생성해서 맵 곳곳에 뿌려주는 함수
void CGameMaster::CreateAndLocaleMonsters()
{
	int random_x;
	int random_y;
	int i = 0;
	char buf[32];

	// 전체 맵의 50%가 몬스터 지역
	// while ( i < ((WORLD_MAP_HEIGHT * WORLD_MAP_WIDTH) >> 2))
	// 테스트용 : 몹이 1마리일 때
	//while ( i < 1 )
	while ( i < ((WORLD_MAP_HEIGHT * WORLD_MAP_WIDTH) >> 2))
	{
		random_x = rand() % WORLD_MAP_HEIGHT;
		random_y = rand() % WORLD_MAP_WIDTH;

		// 몬스터가 이동 가능한 지형에만 할당되도록 변경
		if (NULL == CGameMap::GetInstance()->GetMapType( Position(random_x, random_y) )->GetMonster()
			&& CGameMap::GetInstance()->GetMapType( Position(random_x, random_y) )->IsMovable())
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
	// 타이머를 멈춘다.
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
	// 유저가 이기면 타일의 몹을 삭제하고 몹 자리를 nullptr로 바꾼다
	if (CPlayer::GetInstance()->IsAlive())
	{
		// SetMonster에 Delete가 포함되어 있다
		CGameMap::GetInstance()->GetMapType(CPlayer::GetInstance()->GetPosition())
			->SetMonster(nullptr);

		// 전투 승리시 랜덤 아이템을 얻게 되는 기능 추가.
		ITEM_TYPE RandomItem = static_cast<ITEM_TYPE>( rand() % ITEM_COUNT );

		CPlayer::GetInstance()->GetItem(RandomItem);
	}
	// 유저가 죽으면 게임을 끝낸다
	else
	{
		printf_s("You Are Dead...\n");
		getchar();
		exit(0);
	}
	printf_s("전투 종료! \n 엔터 키를 누르세요!");
	getchar();
	// 여기까지 도달하면 전투 종료이므로 타이머를 다시 시작한다
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

// 게임 종료 조건을 검사한다.
ENDING_TYPE CGameMaster::GameEndCheck()
{
	// 엔딩 조건 1 : 모든 몬스터 전멸
	int IsRestMonsterNum = 0;

	for ( int i = 0; i < WORLD_MAP_HEIGHT; ++i )
	{
		for ( int j = 0; j < WORLD_MAP_WIDTH; ++j )
		{
			// 모든 타일을 돌면서 몬스터가 있는지 검사
			if ( CGameMap::GetInstance()->GetMapType( Position(i, j) )->GetMonster() )
			{
				++IsRestMonsterNum;
			}
		}
	}

	// 남은 몬스터가 하나도 없다면?
	if ( IsRestMonsterNum == 0 )
	{
		return ENDING_MONSTER_ELIMINATION;
	}

	// 종료조건 2 : 공주의 능력치 중 하나가 10을 넘는다.
	int PrincessInt = CPrincess::GetInstance()->GetINT();
	int PrincessStr = CPrincess::GetInstance()->GetSTR();
	int PrincessDex = CPrincess::GetInstance()->GetDEX();

	if (PrincessInt > 10 || PrincessDex > 10 || PrincessStr > 10)
		return ENDING_PRINCESS_DOMINATE;

	// 종료 조건에 해당되지 않으면
	return CONTINUE_GAME;
}

void CGameMaster::EndingScene( ENDING_TYPE Ending )
{
	system("cls");

	// 데코
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
		printf_s("\n당신은 모든 몬스터를 전멸시켰다.\n 당신은 역사상 가장 강력한 섭정으로 이름을 남길 것이다... \n");
		getchar();
		break;
	case ENDING_PRINCESS_DOMINATE:
		printf_s("\n당신은 공주를 훌륭히 키워냈습니다.\n 이제 뒷일은 공주에게 맡겨도 되겠죠... \n");
	// 이 경우 q로 게임 강제 종료에 해당. 그냥 넘긴다.
	case CONTINUE_GAME:
		break;
	}
	printf_s("\n\n 축하합니다! 게임 끝입니다. \n");
	getchar();
}

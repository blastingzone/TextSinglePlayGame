#include "stdafx.h"
#include "GameInput.h"
#include "Player.h"
#include "GameMap.h"
#include "Help.h"
#include <string>
#include <iostream>

CGameInput* CGameInput::m_pInstance = nullptr;

CGameInput::CGameInput(void)
{

}

CGameInput::~CGameInput(void)
{
	
}

CGameInput* CGameInput::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CGameInput();
	}
	return m_pInstance;
}

bool CGameInput::CommandInput()
{
	// 사용자 입력 받기
	std::string userInput;
	std::getline(std::cin, userInput);

	// 입력받은 명령 화면에 출력
	// printf_s("%s \n", userInput.c_str());

	// 이동 명령어
	if ((userInput == "W" || userInput == "w")
		&& CGameMap::GetInstance()->IsMovableCoordinate(CPlayer::GetInstance()->GetPosition(), DIR_UP) )
	{
		CPlayer::GetInstance()->MovePlayer(DIR_UP);
	}
	if (userInput == "S" || userInput == "s"
		&& CGameMap::GetInstance()->IsMovableCoordinate(CPlayer::GetInstance()->GetPosition(), DIR_DOWN) )
	{
		CPlayer::GetInstance()->MovePlayer(DIR_DOWN);
	}
	if (userInput == "A" || userInput == "a"
		&& CGameMap::GetInstance()->IsMovableCoordinate(CPlayer::GetInstance()->GetPosition(), DIR_LEFT) )
	{
		CPlayer::GetInstance()->MovePlayer(DIR_LEFT);
	}
	if (userInput == "D" || userInput == "d"
		&& CGameMap::GetInstance()->IsMovableCoordinate(CPlayer::GetInstance()->GetPosition(), DIR_RIGHT) )
	{
		CPlayer::GetInstance()->MovePlayer(DIR_RIGHT);
	}

	// 스킬 : Fury
	if (userInput == "f" || userInput == "F")
	{
		// 스킬을 사용중이면 끄고 사용중이 아니면 사용하기 시작
		if ( !CPlayer::GetInstance()->GetFuryFlag() )
		{
			CPlayer::GetInstance()->TurnFuryFlag();
			printf_s("당신은 눈이 충혈되는 것을 느낍니다! 몬스터의 기척이 보입니다. \n");
		}
		else
		{
			CPlayer::GetInstance()->TurnFuryFlag();
			printf_s("당신은 진정합니다. \n");
		}
	}

	// 지도 출력
	if (userInput == "M" || userInput == "m")
	{
		CGameMap::GetInstance()->PrintMap();
	}
	// 도움말 출력
	if (userInput == "H" || userInput == "h")
	{
		CHelp::GetInstance()->printHelp();
		// 도움말을 자주 사용하지 않을 것이라고 가정
		CHelp::GetInstance()->ReleaseInstance();
	}
	// 게임 종료
	if (userInput == "Q" || userInput == "q")
	{
		return false;
	}

	return true;
}

void CGameInput::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}


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
	// ����� �Է� �ޱ�
	std::string userInput;
	std::getline(std::cin, userInput);

	// �Է¹��� ��� ȭ�鿡 ���
	// printf_s("%s \n", userInput.c_str());

	// �̵� ��ɾ�
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

	// ��ų : Fury
	if (userInput == "f" || userInput == "F")
	{
		// ��ų�� ������̸� ���� ������� �ƴϸ� ����ϱ� ����
		if ( !CPlayer::GetInstance()->GetFuryFlag() )
		{
			CPlayer::GetInstance()->TurnFuryFlag();
			printf_s("����� ���� �����Ǵ� ���� �����ϴ�! ������ ��ô�� ���Դϴ�. \n");
		}
		else
		{
			CPlayer::GetInstance()->TurnFuryFlag();
			printf_s("����� �����մϴ�. \n");
		}
	}

	// ���� ���
	if (userInput == "M" || userInput == "m")
	{
		CGameMap::GetInstance()->PrintMap();
	}
	// ���� ���
	if (userInput == "H" || userInput == "h")
	{
		CHelp::GetInstance()->printHelp();
		// ������ ���� ������� ���� ���̶�� ����
		CHelp::GetInstance()->ReleaseInstance();
	}
	// ���� ����
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


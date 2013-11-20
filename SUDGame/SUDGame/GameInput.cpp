#include "stdafx.h"
#include "GameInput.h"
#include "Player.h"
#include "GameMap.h"
#include <string>
#include <iostream>

CGameInput* CGameInput::m_pInstance = nullptr;

CGameInput::CGameInput(void)
{

}

CGameInput::~CGameInput(void)
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
	}
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
	if (userInput == "W" || userInput == "w")
	{
		CPlayer::GetInstance()->MovePlayer(DIR_UP);
	}
	if (userInput == "S" || userInput == "s")
	{
		CPlayer::GetInstance()->MovePlayer(DIR_DOWN);
	}
	if (userInput == "A" || userInput == "a")
	{
		CPlayer::GetInstance()->MovePlayer(DIR_LEFT);
	}
	if (userInput == "D" || userInput == "d")
	{
		CPlayer::GetInstance()->MovePlayer(DIR_RIGHT);
	}

	if (userInput == "M" || userInput == "m")
	{
		CGameMap::GetInstance()->PrintMap();
	}

	if (userInput == "Q" || userInput == "q")
	{
		return false;
	}

	return true;
}
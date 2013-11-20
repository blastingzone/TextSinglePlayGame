#pragma once
#include "config.h"
#include <string>

class CCharacter
{
public:
	CCharacter(void);
	virtual ~CCharacter(void);

	void SetName(std::string name) {m_Name = name;}
	void SetPosition(int i, int j) {m_CurrentPosition.x_Coordinate = i; m_CurrentPosition.y_Coordinate = j;}
	
	std::string GetName() {return m_Name;}

	Position GetPosition() {return m_CurrentPosition;}
	bool IsAlive() {return (m_HP > 0 ? true : false);}
	
	void HitCheck(CCharacter* attacker);

	int GetSTR() {return m_STR;}
	int GetDEX() {return m_DEX;}
	int GetINT() {return m_INT;}

protected:
	std::string	m_Name;

	int		m_HP;
	int		m_MP;
	int		m_STR;
	int		m_DEX;
	int		m_INT;

	Position m_CurrentPosition;
};


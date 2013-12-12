#pragma once

class CHelp
{
public:
	CHelp(void);
	~CHelp(void);

	static	CHelp*	GetInstance();
	void			ReleaseInstance();

	void			printHelp();

private:
	static CHelp*	m_pInstance;
};


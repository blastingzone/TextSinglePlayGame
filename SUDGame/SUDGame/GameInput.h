#pragma once
class CGameInput
{
public:
	CGameInput(void);
	~CGameInput(void);

	static CGameInput*		GetInstance();
	void					ReleaseInstance();

	bool					CommandInput();
	

private:
	static CGameInput* m_pInstance;
};


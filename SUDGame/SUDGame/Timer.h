#pragma once

// ������� ��������. �� �� ����� ������ ���°�?
// ������. ��������(����?)
static DWORD				m_PreviousCheckedTime;
static DWORD				m_PresentCheckedTime;
static DWORD				m_DifferentSecond;

class CTimer
{
public:
	CTimer(void);
	~CTimer(void);

	//������ �ð��� ���
	void CalcPassedTime();

	//1�ʰ� �������� Ȯ��
	unsigned int IsPassedOneSecond();

	//Ÿ�̸� �������� �ʱ�ȭ ��
	void ResetTimer()			{	m_DifferentSecond = 0;
									m_PresentCheckedTime = 0;
									m_PreviousCheckedTime = 0; }

	//Ÿ�̸Ӹ� �����忡 ����ֱ� ���� ������ ������ �κ�
	static unsigned int __stdcall ThreadEntry(void* pLPVOID);
};
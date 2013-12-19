#pragma once

// 쓰레드용 전역변수. 좀 더 우아한 접근은 없는가?
// 괜찮다. 문제없어(정말?)
static DWORD				m_PreviousCheckedTime;
static DWORD				m_PresentCheckedTime;
static DWORD				m_DifferentSecond;

class CTimer
{
public:
	CTimer(void);
	~CTimer(void);

	//지나간 시간을 계산
	void CalcPassedTime();

	//1초가 지났는지 확인
	unsigned int IsPassedOneSecond();

	//타이머 변수들을 초기화 함
	void ResetTimer()			{	m_DifferentSecond = 0;
									m_PresentCheckedTime = 0;
									m_PreviousCheckedTime = 0; }

	//타이머를 쓰레드에 집어넣기 위해 형식을 맞춰준 부분
	static unsigned int __stdcall ThreadEntry(void* pLPVOID);
};
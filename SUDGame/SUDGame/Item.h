#pragma once
class CItem
{
public:
	CItem(void);
	virtual ~CItem(void);

protected:
	void UseItem();
	void AbandonItem();
};


#pragma once
#include "COrder.h"

class CMatchRecord
{
public:
	CMatchRecord(double dPrice, int iAmount, COrder taker, COrder maker);
	~CMatchRecord();

public:
	std::string to_string();

private:
	COrder	m_COTaker;
	COrder	m_COMaker;
	double	m_dPrice;
	int		m_iAmount;
};


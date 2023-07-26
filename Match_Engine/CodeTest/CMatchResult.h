#pragma once
#include "COrder.h"
#include "CMatchRecord.h"

class CMatchResult
{
public:
	CMatchResult(COrder taker);
	~CMatchResult();
	bool bAdd(double dPrice, int iamount, COrder maker);
	std::string to_string();

private:
	COrder m_COTaker;
	std::vector<CMatchRecord> m_vecMatchRecords;
};


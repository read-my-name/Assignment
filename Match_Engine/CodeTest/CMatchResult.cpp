#include "CMatchResult.h"

CMatchResult::CMatchResult(COrder taker)
	:m_COTaker(taker)
{
}

CMatchResult::~CMatchResult()
{

}

bool CMatchResult::bAdd(double dPrice, int iAmt, COrder maker)
{
	//push_back needs to have temporary object, using emplace_back can reduce the space
	//CMatchRecord CMR1(dPrice, iAmt, this->m_COTaker, maker);
	//this->m_vecMatchRecords.push_back(CMR1);
	this->m_vecMatchRecords.emplace_back(dPrice, iAmt, this->m_COTaker, maker);
	return true;
}

std::string CMatchResult::to_string()
{
	std::ostringstream oss;
	oss << __FUNCTION__;
	std::string strRes("");
	if (this->m_vecMatchRecords.empty())
	{
		oss << " [0 Match Records Found!]";
		strRes = oss.str();
		DbgLogTiming.bLogToFile(LOG_MATCHRESULT, strRes);
		return LOG_MATCHRESULT + std::string(" [ 0 Match Records Found! ]\n");
	}
	oss.str("");
	oss << " [ " << this->m_vecMatchRecords.size() << " Match Records! ]\n";
	//strRes = oss.str();
	//DbgLogTiming.bLogToFile(LOG_MATCHRESULT, strRes);
	bool isFirst = true;
	oss << "*** ";
	for (CMatchRecord& record : m_vecMatchRecords) 
	{
		if (!isFirst) 
		{
			oss << ", ";
		}
		isFirst = false;
		oss << record.to_string();
	}
	oss << " ***\n";
	strRes = oss.str();
	DbgLogTiming.bLogToFile(LOG_MATCHRESULT, strRes);
	//std::cout << strRes;
	return strRes;
}
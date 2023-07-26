#include "CMatchRecord.h"

CMatchRecord::CMatchRecord(double dPrice, int iAmount, COrder taker, COrder maker)
	: m_dPrice(dPrice), m_iAmount(iAmount), m_COTaker(taker), m_COMaker(maker)
{
}

CMatchRecord::~CMatchRecord()
{

}

std::string CMatchRecord::to_string()
{
	std::ostringstream oss;
	oss << " [ " << this->m_dPrice << ", " << this->m_iAmount << " ] ";
	std::string strRes = oss.str();
	DbgLogTiming.bLogToFile(LOG_MATCHRECORD, strRes);
	//std::cout << strRes << std::endl;
	return strRes;
}
#include "COrder.h"

COrder::COrder(int id, CDirection::eDirection eDir, double dPrice, int iAmount)
{
	m_id			= id;
	m_dPrice		= dPrice;
	m_iAmount		= iAmount;
	m_eDir			= eDir;
}

COrder::~COrder()
{

}

int COrder::getID() 
{
	return this->m_id;
}

double COrder::getPrice() 
{
	return this->m_dPrice;
}

bool COrder::setPrice(double dPrice)
{
	bool bRes = true;
	this->m_dPrice = dPrice;
	return bRes;
}

int COrder::getAmount() 
{
	return this->m_iAmount;
}

bool COrder::setAmount(int iAmount)
{
	bool bRes = true;
	this->m_iAmount = iAmount;
	return bRes;
}

std::string COrder::getDirection() 
{
	std::string str = m_eDir == CDirection::eBUY ? "BUY" : "SELL";
	//std::cout << str << "\n";
	return str;
}

CDirection::eDirection COrder::getDir()
{
	return this->m_eDir;
}

std::string COrder::to_string()
{
	/*std::string szRes;
	char chBuf[100] = { 0 };
	getDirection();
	sprintf(chBuf, "%s-%s	: Id(%d) Direction() Price(%lf) Amount(%d)\n", LOG_CORDER, __FUNCTION__, this->m_id, this->getPrice(), this->getAmount());
	szRes = chBuf;*/

	std::ostringstream oss;
	//oss << LOG_ORDERBOOK << " Action(" << __FUNCTION__ << ")" << " ID: " << this->getID() << ", Price: " << this->getPrice() << ", Direction: " << this->getDirection() << ", Amount: " << this->getAmount() << "\n";
	oss << __FUNCTION__;
	oss << " ID: " << this->getID() << ", Price: " << this->getPrice() << ", Direction: " << this->getDirection() << ", Amount: " << this->getAmount() << "\n";
	std::string strRes = oss.str();
	DbgLogTiming.bLogToFile(LOG_ORDER, strRes);
	//std::cout << strRes << std::endl;
	
	return strRes;
}
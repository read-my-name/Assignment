#pragma once
#include "include.h"
#include "COrder.h"
#include "COrderKey.h"

class COrderBook
{
public:
	//COrderBook();
	COrderBook(CDirection::eDirection eDir);
	~COrderBook();

public:
	//std::map<COrderKey, COrder> getMap();
	COrder *getFirst();
	bool bAdd(COrder COrder);
	bool bRemove(COrder COrder);
	int iGetSize();
	std::string strPrint(COrder COrder, std::string strAction);
	std::string to_string();

private:
	struct SORT_BUY 
	{
		bool operator()(const COrderKey& co1, const COrderKey& co2) const 
		{//co1 is the member variable, and co2 is the input
			if (co2.m_dPrice < co1.m_dPrice) 
			{
				return true;  // co1 should come before co2
			}
			else if (co2.m_dPrice > co1.m_dPrice) 
			{
				return false; // co2 should come before co1
			}
			else 
			{
				return co1.m_id < co2.m_id; // If prices are the same, compare by m_id
			}
		}
	};
	struct SORT_SELL 
	{
		bool operator()(const COrderKey& co1, const COrderKey& co2) const 
		{
			if (co2.m_dPrice > co1.m_dPrice) 
			{
				return true;  // co1 should come before co2
			}
			else if (co2.m_dPrice < co1.m_dPrice) 
			{
				return false; // co2 should come before co1
			}
			else 
			{
				return co1.m_id < co2.m_id; // If prices are the same, compare by m_id
			}
		}
	};

public:
	CDirection::eDirection					m_eDir;
	static std::map<COrderKey, COrder, SORT_BUY>	m_mapBookBuy;
	static std::map<COrderKey, COrder, SORT_SELL>	m_mapBookSell;
	
};


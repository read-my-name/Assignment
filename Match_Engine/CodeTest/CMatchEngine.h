#pragma once
#include "include.h"
#include "COrderBook.h"
#include "CMatchResult.h"

class CMatchEngine
{
//Taker: Places a market order, which is immediately matched against existing orders in the order book.
//Maker : Places a limit order, which is added to the order book and waits for a taker to match it.
public:
	CMatchEngine();
	~CMatchEngine();
	

public:
	CMatchResult cmrProcessOrder(COrder co);
	std::string to_string();

private:
	double m_dMarketPrice;
	COrderBook m_cobBuyBook;
	COrderBook m_cobSellBook;

private:
	// Signum function in C++
	template <typename T>
	int signum(T val)
	{
		// true = 1, false = 0
		// 1 if val > 0, 0 if val = 0, -1 if val < 0
		return (T(0) < val) - (val < T(0));
	}
	CMatchResult cmrProcessOrder(COrder coTaker, COrderBook maker, COrderBook restingBook);
	bool bCancel(COrder co);
};


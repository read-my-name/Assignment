#include "CMatchEngine.h"

CMatchEngine::CMatchEngine()
	:m_cobBuyBook(CDirection::eBUY), m_cobSellBook(CDirection::eSELL)
{
	this->m_dMarketPrice		= 0.0;
}

CMatchEngine::~CMatchEngine()
{

}

CMatchResult CMatchEngine::cmrProcessOrder(COrder co)
{
	switch (co.getDir())
	{
		case CDirection::eBUY:
			return cmrProcessOrder(co, this->m_cobSellBook, this->m_cobBuyBook);
		case CDirection::eSELL:
			return cmrProcessOrder(co, this->m_cobBuyBook, this->m_cobSellBook);
		default:
			throw std::invalid_argument("Invalid direction.");
	}
}

CMatchResult CMatchEngine::cmrProcessOrder(COrder coTaker, COrderBook maker, COrderBook restingBook)
{
	CMatchResult matchResult(coTaker);
	std::ostringstream oss;
	std::string strRes("");
	for (;;)
	{
		COrder *coMaker = maker.getFirst();
		if (coMaker == nullptr)
		{
			oss << __FUNCTION__ << " No Element Returned\n";
			strRes = oss.str();
			DbgLogTiming.bLogToFile(LOG_MATCHENGINE, strRes);
			oss.str("");
			break;
		}

		if ((coTaker.getDir() == CDirection::eBUY) && (coTaker.getPrice() < coMaker->getPrice()))
		{
			/*std::cout << "Taker < Maker: " << coTaker.getPrice() << " > " << coMaker->getPrice() << "\n";
			std::cout << "Checking..\n";
			std::cout << coMaker->to_string();
			std::cout << "Done Checking..\n";*/
			break;
		}
		else if ((coTaker.getDir() == CDirection::eSELL) && (coTaker.getPrice() > coMaker->getPrice()))
		{
			break;
		}

		//Indicate the market price
		double dMarketPrice = coMaker->getPrice();
		
		//take lower amount
		int iAmtMatched = ((coTaker.getAmount() < coMaker->getAmount()) ? (coTaker.getAmount()) : (coMaker->getAmount()));
		
		//std::cout << LOG_MATCHENGINE << " | " << __FUNCTION__ << " Matket Price: " << dMarketPrice << "\n";
		//std::cout << "Amount Matched: " << iAmtMatched << ", Taker: " << coTaker.getAmount() << ", Maker: " << coMaker->getAmount() << "\n";

		matchResult.bAdd(coMaker->getPrice(), iAmtMatched, *coMaker);

		//Renew the amount
		coTaker.setAmount(coTaker.getAmount() - iAmtMatched);
		coMaker->setAmount(coMaker->getAmount() - iAmtMatched);

		//std::cout << "Maker Cleared? " << signum(coMaker->getAmount()) << "\n";
		//if makerOrder is fully matched, remove it
		if (signum(coMaker->getAmount()) == 0)
		{
			//std::cout << "Remove From Book " << "\n";
			bool bRes = maker.bRemove(*coMaker);
			//std::cout << "Remove From Resting Book " << (bRes ? "SUCCESS" : "FAIL") << "\n";
		}

		//std::cout << "Taker Cleared? " << signum(coTaker.getAmount()) << "\n";
		//if takerOrder is fully matched, break the loop
		if (signum(coTaker.getAmount()) == 0)
		{
			//std::cout << "Break From Matching " << "\n";
			break;
		}
	}
	//oss << "Taker Cleared? Resting Book Add? " << signum(coTaker.getAmount()) << "\n";
	//std::cout << "Taker Cleared? Resting Book Add? " << signum(coTaker.getAmount()) << "\n";
	if (signum(coTaker.getAmount()) > 0)
	{
		restingBook.to_string();
		bool bRes = restingBook.bAdd(coTaker);
		//std::cout << "Add to Resting Book " << (bRes ? "SUCCESS" : "FAIL") << "\n";
	}
	/*std::cout << "End of " << __FUNCTION__ << "\n";*/
	oss << "Matching Done!";
	strRes = oss.str();
	DbgLogTiming.bLogToFile(LOG_MATCHENGINE, strRes);
	//std::cout << strRes;

	return matchResult;
}

bool CMatchEngine::bCancel(COrder co)
{
	COrderBook book = co.getDir() == CDirection::eBUY ? this->m_cobBuyBook : this->m_cobSellBook;
	return book.bRemove(co);
}

std::string CMatchEngine::to_string()
{
	std::ostringstream oss;
	oss << "\n-------------------------------------------\n";
	oss << "--- Sell Book: " << this->m_cobSellBook.to_string();
	oss << "----------\n";
	oss << "--- The Market Price: " << this->m_dMarketPrice;
	oss << "\n----------\n";
	oss << "--- Buy Book: " << this->m_cobBuyBook.to_string();
	oss << "-------------------------------------------\n";

	std::string strRes = oss.str();
	DbgLogTiming.bLogToFile(LOG_MATCHENGINE, strRes);
	return strRes;
}
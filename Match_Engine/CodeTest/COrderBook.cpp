#include "COrderBook.h"

// Define the static member variables outside the class (in the .cpp file)
std::map<COrderKey, COrder, COrderBook::SORT_BUY> COrderBook::m_mapBookBuy;
std::map<COrderKey, COrder, COrderBook::SORT_SELL> COrderBook::m_mapBookSell;

COrderBook::COrderBook(CDirection::eDirection eDir)
{
	this->m_eDir = eDir;
}

COrderBook::~COrderBook()
{
    //std::cout << __FUNCTION__ << "\n";
}

COrder* COrderBook::getFirst() 
{
    std::ostringstream oss;
    std::string strRes("");
    oss << __FUNCTION__;
    if (this->m_eDir == CDirection::eBUY) 
    {
        oss << " BUY Book: " << "Size: " << this->m_mapBookBuy.size() << "\n";
        strRes = oss.str();
        DbgLogTiming.bLogToFile(LOG_ORDERBOOK, strRes);
        //std::cout << "BUY Book: " << "Size: " << this->m_mapBookBuy.size() << " " << (this->m_mapBookBuy.empty() ? "IS EMPTY\n" : "NOT EMPTY\n");
        //return this->m_mapBookBuy.empty() ? nullptr : &(this->m_mapBookBuy.begin()->second);
        if (this->m_mapBookBuy.empty())
        {
            return nullptr;
        }
        return &(this->m_mapBookBuy.begin()->second);
    }
    else 
    {
        oss << " SELL Book: " << "Size: " << this->m_mapBookBuy.size() << "\n";
        strRes = oss.str();
        DbgLogTiming.bLogToFile(LOG_ORDERBOOK, strRes);
        if (this->m_mapBookSell.empty())
        {
            return nullptr;
        }
        return &(this->m_mapBookSell.begin()->second);
    }
    return nullptr;
}

bool COrderBook::bAdd(COrder CO)
{
    //std::cout << strPrint(CO, __FUNCTION__);
    std::ostringstream oss;
    std::string strRes("");
    oss << __FUNCTION__;
   
    std::pair<std::map<COrderKey, COrder>::iterator, bool> inRes;
    if (this->m_eDir == CDirection::eBUY)
    {
        oss << " BUY_BOOK Price: " << CO.getPrice() << ", Amount: " << CO.getAmount();
        strRes = oss.str();
        DbgLogTiming.bLogToFile(LOG_ORDERBOOK, strRes);
        //std::cout << "BUY Book Added: " << CO.getPrice() << " " << CO.getAmount() << "\n";
        inRes = this->m_mapBookBuy.insert(std::make_pair(COrderKey(CO.getID(), CO.getPrice()),CO));
        return inRes.second ? true : false;
    }
    else
    {
        oss << " SELL_BOOK Price: " << CO.getPrice() << ", Amount: " << CO.getAmount();
        strRes = oss.str();
        DbgLogTiming.bLogToFile(LOG_ORDERBOOK, strRes);
        //std::cout << "SELL Book Added: " << CO.getPrice() << " " << CO.getAmount() << "\n";
        inRes = this->m_mapBookSell.insert(std::make_pair(COrderKey(CO.getID(), CO.getPrice()), CO));
        return inRes.second ? true : false;
    }
    return false;
}

bool COrderBook::bRemove(COrder CO)
{
    std::ostringstream oss;
    std::string strRes("");
    oss << __FUNCTION__;
    
    //std::cout << strPrint(CO, __FUNCTION__);
    size_t sizeRes;
    if (this->m_eDir == CDirection::eBUY)
    {
        oss << " BUY_BOOK Price: " << CO.getPrice() << ", Amount: " << CO.getAmount();
        strRes = oss.str();
        DbgLogTiming.bLogToFile(LOG_ORDERBOOK, strRes);
        sizeRes = this->m_mapBookBuy.erase(COrderKey(CO.getID(), CO.getPrice()));
        return sizeRes == 1 ? true : false;
    }
    else
    {
        oss << " SELL_BOOK Price: " << CO.getPrice() << ", Amount: " << CO.getAmount();
        strRes = oss.str();
        DbgLogTiming.bLogToFile(LOG_ORDERBOOK, strRes);
        sizeRes = this->m_mapBookSell.erase(COrderKey(CO.getID(), CO.getPrice()));
        return sizeRes == 1 ? true : false;
    }
    return false;
}

int COrderBook::iGetSize()
{
    if (this->m_eDir == CDirection::eBUY)
    {
        return int(this->m_mapBookBuy.size());
    }
    else
    {
        return int(this->m_mapBookSell.size());
    }
    return -1;
}

std::string COrderBook::strPrint(COrder CO, std::string sAct)
{
    std::ostringstream oss;
    oss << LOG_ORDERBOOK << " Action(" << sAct << ")" << " ID: " << CO.getID() << ", Price: " << CO.getPrice() << ", Direction: " << CO.getDirection() << ", Amount: " << CO.getAmount() << "\n";
    std::string strRes = oss.str();
    //std::cout << strRes << std::endl;
    return strRes;
}

std::string COrderBook::to_string()
{
    std::ostringstream oss;
    oss << "\n";

    if (this->m_eDir == CDirection::eBUY)
    {   
        oss << "=== Items of The Buy Book\n";
        for (auto& pair : this->m_mapBookBuy) 
        {
            oss << "=== Order: { ID:" << pair.first.m_id << ", Price:" << pair.first.m_dPrice
                << ", Amount:" << pair.second.getAmount() << ", Direction:" << pair.second.getDirection() << " }\n";
        }
        
    }
    else
    {
        oss << "=== Items of The Sell Book\n";
        for (auto& pair : this->m_mapBookSell)
        {
            oss << "=== Order: { ID:" << pair.first.m_id << ", Price:" << pair.first.m_dPrice
                << ", Amount:" << pair.second.getAmount() << ", Direction:" << pair.second.getDirection() << " }\n";
        }
    }
    oss << "=== End Of The Order Book\n";
    std::string strRes = oss.str();
    DbgLogTiming.bLogToFile(LOG_ORDERBOOK, strRes);
    //std::cout << strRes << std::endl;
    return strRes;
}






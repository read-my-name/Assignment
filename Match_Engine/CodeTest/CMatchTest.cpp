#include "CMatchTest.h"

int CMatchTest::m_id = 0;

CMatchTest::CMatchTest()
{
    //this->m_id = 0;
}

CMatchTest::~CMatchTest()
{

}

COrder CMatchTest::coCreate(std::string strInput, char cDelimeter)
{
    this->m_id++;
    std::istringstream iss(strInput);
    CDirection::eDirection eDir = CDirection::eDefault;
    std::string strDir(""), strPrice(""), strAmt("");
    double dPrice = 0.0;
    int iAmt = 0;

    std::getline(iss, strDir, cDelimeter);
    std::getline(iss, strPrice, cDelimeter);
    std::getline(iss, strAmt, cDelimeter);

    // Convert the strDir to all upper case
    std::transform(strDir.begin(), strDir.end(), strDir.begin(), ::toupper);

    if (strDir == "BUY")
    {
        eDir = CDirection::eBUY;
    }
    else if (strDir == "SELL")
    {
        eDir = CDirection::eSELL;
    }
    else 
    {
        throw std::invalid_argument("Invalid direction in the input: " + strInput);
    }
    
    dPrice  = std::stod(strPrice);
    iAmt    = std::stoi(strAmt);

    return COrder(m_id, eDir, dPrice, iAmt);
}

void CMatchTest::vEngineTest()
{
    /*std::string strInput = R"(
        buy/2082.34/1
        sell/2087.6/2
        buy/2087.8/1
        buy/2085.01/5
        sell/2088.02/3
        sell/2087.60/6
        buy/2081.11/7
        buy/2086.0/3
        buy/2088.33/1
        sell/2086.54/2
        sell/2086.55/5
        buy/2086.55/3
    )";*/

    std::ostringstream oss;
    std::string strRes("");

    std::vector<std::string> vInput{
        "buy/2082.34/1",
        "sell/2087.6/2",
        "buy/2087.8/1",
        "buy/2085.01/5",
        "sell/2088.02/3",
        "sell/2087.60/6",
        "buy/2081.11/7",
        "buy/2086.0/3",
        "buy/2088.33/1",
        "sell/2086.54/2",
        "sell/2086.55/5",
        "buy/2086.55/3"
    };
    std::cout << "Start Testing...\n";

    CMatchEngine cme;
    //std::istringstream iss(strInput);
    //std::string line;
    //while (std::getline(iss, line)) 
    for(std::string line : vInput)
    {
        if (sTrim(line) == "")
        {
            continue;
        }
        COrder co = coCreate(line, '/');
        oss << "\n=============================================Start===================================\n";
        CMatchResult result = cme.cmrProcessOrder(co);

        //std::ostringstream oss;
        oss << "\n-------------------------------------------\n";
        oss << co.to_string();
        oss << cme.to_string();
        oss << result.to_string();
        oss << "\n-------------------------------------------\n";
        oss << "=============================================End=====================================\n";
        strRes = oss.str();
        DbgLogTiming.bLogToFile(LOG_MATCHTEST, strRes);
        //std::cout << strRes;
    }
}

void CMatchTest::vEngineStart(std::string strMsg)
{
    std::ostringstream oss;
    std::string strRes("");
    CMatchEngine cme;
    std::istringstream iss(strMsg);
    std::string line;

    while (std::getline(iss, line)) 
    {
        if (sTrim(line) == "")
        {
            continue;
        }
        COrder co = coCreate(line, '/');
        oss << "\n=============================================Start===================================\n";
        CMatchResult result = cme.cmrProcessOrder(co);

        //std::ostringstream oss;
        oss << "\n-------------------------------------------\n";
        oss << co.to_string();
        oss << cme.to_string();
        oss << result.to_string();
        oss << "\n-------------------------------------------\n";
        oss << "=============================================End=====================================\n";
        strRes = oss.str();
        DbgLogTiming.bLogToFile(LOG_MATCHTEST, strRes);
    }
}

// Trim leading and trailing whitespace from a string
std::string CMatchTest::sTrim(std::string str) 
{
    auto first = std::find_if_not(str.begin(), str.end(), [](int c) { return std::isspace(c); });
    auto last = std::find_if_not(str.rbegin(), str.rend(), [](int c) { return std::isspace(c); }).base();
    return (first < last) ? std::string(first, last) : "";
}


#pragma once
class CDirection
{
public:
	enum eDirection
	{
		eDefault = -1,
		eBUY,
		eSELL
	};

#define LOG_ORDER		"ORDER"
#define LOG_ORDERKEY	"ORDER_KEY"
#define LOG_ORDERBOOK	"ORDER_BOOK"
#define LOG_MATCHENGINE "MATCH_ENGINE"
#define LOG_MATCHRECORD "MATCH_RECORD"
#define LOG_MATCHRESULT "MATCH_RESULT"

#define LOG_SERVER		"LOG_SERVER"

#define LOG_MATCHTEST	"MATCH_TEST"
};


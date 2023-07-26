#pragma once
#include "include.h"
#include "COrder.h"
#include "CMatchEngine.h"

class CMatchTest
{
public:
	CMatchTest();
	~CMatchTest();
public:
	COrder coCreate(std::string strInput, char cDelimeter);
	void vEngineTest();
	void vEngineStart(std::string strMsg);
	std::string sTrim(std::string strInput);

private:
	static int m_id;
};


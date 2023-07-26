#pragma once
#include "include.h"
//#include "CLogInstance.h"

class CLogger
{
public:
	CLogger(const CLogger&) = delete; //delete any constructor
	CLogger &operator=(const CLogger&) = delete;

	//static member function to access the logger instance
	static CLogger& getInstance();

public:
	bool bCreateDirectory(const std::string& strPath);
	bool bLogToFile(std::string strLog, std::string strMsg);
	
private:
	CLogger(); // Private instance;
	std::ofstream m_outLogFile;
	static std::string m_strPath;
	std::string m_strFile;
};

extern CLogger& DbgLogTiming;


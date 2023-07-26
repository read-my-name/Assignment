#pragma once
#include "Include/include.h"
class CClient
{
public:
	CClient(std::string strIp, int iPort);
	~CClient();

public:
	bool bClientCreate();
	bool bClientSend(std::string strMsg);
	bool bClientClose();

private:
	int m_iPort;
	std::string m_strIp;

	int m_iClientSocket;
	#define BUFFER_SIZE 1024
};


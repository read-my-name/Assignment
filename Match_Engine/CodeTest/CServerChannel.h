#pragma once
#include "include.h"
#include <thread>
#include <cstring>
#include <functional>

class CServerChannel
{
public:
	// Function type for the callback
	using MsgCallback = std::function<void(const std::string&)>;

	CServerChannel();
	~CServerChannel();
	
public:
	bool bServerStart();
	bool bServerCreate();
	bool bServerAccept();
	bool bServerClose();
	//void vHandleClient(int iClient);
	void OnMsgReceived(const std::string& strMsg);
	void Start(MsgCallback callback);
	
private:
	std::string m_strIp;
	std::vector<int> m_vecPort;
	int m_iBackLog;
	int m_iMaxClient;
	std::vector<std::pair<int, std::string>> m_vecClientSocs;
	std::vector<std::pair<int, std::string>> m_vecServerSocs;
	std::vector<std::thread> m_vecServerThread;

	//int m_iServer, m_iNewSocket;
	#define BUFFER_SIZE 1024

private:
	void vServerCreate(std::string strIp, int iPort);
	MsgCallback m_msgCallback;
};


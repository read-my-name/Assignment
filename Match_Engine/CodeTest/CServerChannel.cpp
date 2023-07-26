#include "CServerChannel.h"

CServerChannel::CServerChannel()
	:m_strIp("127.0.0.1"), m_iBackLog(5), m_iMaxClient(10)
{
	m_vecPort.push_back(661);
	m_vecPort.push_back(662);
	WSADATA wsaData;
	int iRes = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iRes != 0) 
	{
		std::cerr << "WSAStartup failed: " << iRes << std::endl;
	}
}

CServerChannel::~CServerChannel()
{
	std::cout << __FUNCTION__ << "\n";
}

bool CServerChannel::bServerStart()
{
	for (int iPort : m_vecPort)
	{
		std::cout << "Starting Server at Port: " << iPort << "\n";
		//using lambda function to pass member function
		std::thread serverThread([this, iPort]() {
				this->vServerCreate(m_strIp, iPort);
		});
		this->m_vecServerThread.push_back(std::move(serverThread));
	}
	
	for (std::thread& thread : this->m_vecServerThread)
	{
		thread.join();
	}
	return true;
}

bool CServerChannel::bServerCreate()
{
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t clientAddrSize = sizeof(clientAddr);
	
	for (int iPort : m_vecPort)
	{
		int iServer = socket(AF_INET, SOCK_STREAM, 0);
		if (iServer == INVALID_SOCKET)
		{
			int ierr = WSAGetLastError();
			std::cerr << "Failed to Create Socket: " << ierr << ", For Port: " << iPort << "\n";
			WSACleanup();
			continue;
		}

		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(iPort);
		/*serverAddr.sin_addr.s_addr	= INADDR_ANY;*/
		serverAddr.sin_addr.s_addr = inet_addr(m_strIp.c_str());

		std::cout << __FUNCTION__ << "Server Binds <" << iPort << " >" << "...\n";
		if (bind(iServer, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		{
			int ierr = WSAGetLastError();
			std::cerr << "Failed to Bind Socket: " << ierr << ", For Port: " << iPort << "\n";
			closesocket(iServer);
			//WSACleanup();
			continue;
		}

		if (listen(iServer, m_iBackLog) == SOCKET_ERROR)
		{
			int ierr = WSAGetLastError();
			std::cerr << "Failed to Listen Socket: " << ierr << ", For Port: " << iPort << "\n";
			closesocket(iServer);
			//WSACleanup();
			//return false;
			continue;
		}

		m_vecServerSocs.push_back(std::make_pair(iServer, std::to_string(iPort)));
		std::cout << __FUNCTION__ << "Server Listening on Port <" << iPort << " >...\n";
	}

	return false;
}

void CServerChannel::vServerCreate(std::string strIp, int iPort)
{
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t clientAddrSize = sizeof(clientAddr);

	int iServer = socket(AF_INET, SOCK_STREAM, 0);
	if (iServer == INVALID_SOCKET)
	{
		int ierr = WSAGetLastError();
		std::cerr << "Failed to Create Socket: " << ierr << ", For Port: " << iPort << "\n";
		//closesocket(m_iServer);
		WSACleanup();
		return;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(iPort);
	/*serverAddr.sin_addr.s_addr	= INADDR_ANY;*/
	serverAddr.sin_addr.s_addr = inet_addr(m_strIp.c_str());

	std::cout << __FUNCTION__ << "Server Binds <" << iPort << " >" << "...\n";
	if (bind(iServer, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int ierr = WSAGetLastError();
		std::cerr << "Failed to Bind Socket: " << ierr << ", For Port: " << iPort << "\n";
		closesocket(iServer);
		//WSACleanup();
		return;
	}

	if (listen(iServer, m_iBackLog) == SOCKET_ERROR)
	{
		int ierr = WSAGetLastError();
		std::cerr << "Failed to Listen Socket: " << ierr << ", For Port: " << iPort << "\n";
		closesocket(iServer);
		//WSACleanup();
		//return false;
		return;
	}

	m_vecServerSocs.push_back(std::make_pair(iServer, std::to_string(iPort)));
	std::cout << __FUNCTION__ << "Server Listening on Port <" << iPort << " >...\n";
}

bool CServerChannel::bServerAccept()
{
	if (m_vecServerSocs.empty())
	{
		std::cerr << "No Valid Server Exisitng! " << "\n";
		//closesocket(m_iServer);
		WSACleanup();
		return false;
	}

	// Create a set to hold the client sockets
	struct sockaddr_in clientAddr;
	socklen_t clientAddrSize = sizeof(clientAddr);
	fd_set clientSet;
	FD_ZERO(&clientSet);
	char cBuf[BUFFER_SIZE] = { 0 };

	for (std::pair<int, std::string> iServer : m_vecServerSocs) 
	{
		FD_SET(iServer.first, &clientSet);
	}
	
	while (true)
	{
		fd_set readSet = clientSet;
		// Use select to monitor active sockets
		if (select(m_iMaxClient + 1, &readSet, nullptr, nullptr, nullptr) == SOCKET_ERROR)
		{
			int ierr = WSAGetLastError();
			std::cerr << "Failed to Select Socket: " << ierr << "\n";
			break;
		}
		//Check for new connections
		for (std::pair<int, std::string> iServer : m_vecServerSocs)
		{
			if (FD_ISSET(iServer.first, &readSet))
			{
				int iNewSocket = accept(iServer.first, (struct sockaddr*)&clientAddr, &clientAddrSize);
				if (iNewSocket == INVALID_SOCKET)
				{
					int ierr = WSAGetLastError();
					std::cerr << "Failed to Accept Socket: " << iServer.first << ", Error: " << ierr << "\n";
					closesocket(iServer.first);
					WSACleanup();
					continue;
				}

				char clientIP[INET_ADDRSTRLEN] = { 0 };
				inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
				/*std::cout << "New Client Connected, IP: " << clientIP << ":" << (clientAddr.sin_port) << "\n";*/
				std::cout << "Client Connected IP: " << clientIP << ":" << iServer.second << "\n";

				FD_SET(iNewSocket, &clientSet);
				m_vecClientSocs.push_back(std::make_pair(iNewSocket, iServer.second));
			}

			// Handle Data from client
			for (std::vector<std::pair<int, std::string>>::iterator it = m_vecClientSocs.begin(); it != m_vecClientSocs.end(); )
			{
				int iClientSoc = it->first;
				if (FD_ISSET(iClientSoc, &readSet))
				{
					int iErr = recv(iClientSoc, cBuf, BUFFER_SIZE, 0);
					if (iErr <= 0)
					{
						std::cout << "Client Disconnected Port: " << it->second << "\n";
						FD_CLR(iClientSoc, &clientSet);
						// Update the iterator to the next element after erasing
						it = m_vecClientSocs.erase(it);
						closesocket(iClientSoc);
					}
					else if (iErr > 0)
					{
						send(iClientSoc, cBuf, iErr, 0);
						cBuf[iErr] = '\0';
						std::cout << "Recieved From Client: " << cBuf << "\n";
						m_msgCallback(cBuf);
						++it; //Move the iterator to the next element
					}
				}
				else
				{
					++it;
				}
			}
		}
	}
	
	return false;
}

bool CServerChannel::bServerClose()
{
	for (std::pair<int,std::string> iClient : m_vecClientSocs)
	{
		closesocket(iClient.first);
	}
	for(std::pair<int,std::string> iServer : m_vecServerSocs)
	{
		closesocket(iServer.first);
		WSACleanup();
	}
	return false;
}

void CServerChannel::OnMsgReceived(const std::string& strMsg)
{
	//std::cout << "CallBack: " << strMsg << "\n";
	std::ostringstream oss;
	oss << __FUNCTION__;
	oss << " Message Received From Clients: " << strMsg;
	std::string strRes = oss.str();
	DbgLogTiming.bLogToFile(LOG_SERVER, strRes);
}

void CServerChannel::Start(MsgCallback callback)
{
	this->m_msgCallback = std::move(callback);
}

#include "CClient.h"

CClient::CClient(std::string strIp, int iPort)
{
    this->m_strIp = "127.0.0.1";
    this->m_iPort = 661;

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) 
    {
        std::cerr << "Failed to initialize winsock." << std::endl;
    }
}

CClient::~CClient()
{
    std::cout << __FUNCTION__ << "\n";
}

bool CClient::bClientCreate()
{
    //int iClient;
    struct sockaddr_in serverAddr;
    char cBuf[BUFFER_SIZE] = { 0 };

    m_iClientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_iClientSocket == INVALID_SOCKET)
    {
        int ierr = WSAGetLastError();
        std::cerr << "Failed to Create Socket: " << ierr << ", For Port: " << m_iPort << "\n";
        WSACleanup();
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(m_iPort);
    serverAddr.sin_addr.s_addr = inet_addr(m_strIp.c_str());

    if (connect(m_iClientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        int ierr = WSAGetLastError();
        std::cerr << "Failed to Connect Socket: " << ierr << ", For Port: " << m_iPort << "\n";
        closesocket(m_iClientSocket);
        WSACleanup();
        return false;
    }

    std::cout << "Connected to server: Port[" << m_iPort << ", " << m_iClientSocket << "]\n";

    //// Send messages without waiting for a reply
    //const char* messages[] = 
    //{
    //    "Hello from client 1",
    //    "Client 1 message 2",
    //    "Client 1 message 3",
    //    "Goodbye from client 1" 
    //};

    //for (const char* msg : messages) 
    //{
    //    send(m_iClientSocket, msg, strlen(msg), 0);
    //    std::cout << "Sent: " << msg << std::endl;
    //    std::this_thread::sleep_for(std::chrono::seconds(1));
    //}

    return true;
}

bool CClient::bClientSend(std::string strMsg)
{
    /*const char* messages[] =
    {
        "Hello from client 1",
        "Client 1 message 2",
        "Client 1 message 3",
        "Goodbye from client 1"
    };*/

    //char* cMsg[BUFFER_SIZE];
    const char *cMsg = strMsg.c_str();

    send(m_iClientSocket, cMsg, strlen(cMsg), 0);
    std::cout << "Sent: " << cMsg << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return true;
}

bool CClient::bClientClose()
{
    closesocket(m_iClientSocket);
    WSACleanup();
    std::cout << "Disconnet From Server!\n";
    return true;
}
#include "CLogger.h"

std::string CLogger::m_strPath("");
CLogger& DbgLogTiming = CLogger::getInstance(); // Define the global instance here

CLogger::CLogger()
{
    std::string strPath = "LOGS";
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    char cBuf[20];
    std::strftime(cBuf, sizeof(cBuf), "_%Y%m%d_%H%M%S", std::localtime(&time));
    std::string strFile = strPath;
    strFile += std::string("\\Log1");
    strFile += std::string(cBuf);
    strFile += std::string(".txt");
    m_strFile = strFile;
    m_outLogFile.open(strFile, std::ios::out);
    if (m_outLogFile.is_open())
    {
        // Write the log message with timing to the file
        m_outLogFile << "[ Here Is The Debug Log File ]\n";
        m_outLogFile << "==================================================================\n";
        m_outLogFile.close();
    }
    bCreateDirectory(strPath);
}

CLogger& CLogger::getInstance()
{
    // Guaranteed to be initialized once and only once
    static CLogger s_instance;
    return s_instance;
}

bool CLogger::bCreateDirectory(const std::string& strPath)
{
    int iRes = _mkdir(strPath.c_str()); // Need to implement direct.h
    this->m_strPath = strPath;
    if (iRes == 0)
    {
        std::cout << "Directory created: " << strPath << "\n";
    }
    else
    {
        std::cout << "Directory already exists or couldn't be created: " << strPath << "\n";
    }
    return true;
}


bool CLogger::bLogToFile(std::string strLog, std::string strMsg)
{
    // Get the current date and time
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    // Convert the time to a human-readable format
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));
    std::string formattedTime = buffer;

    // Open the log file in append mode
    std::string strFile = m_strFile;
    m_outLogFile.open(strFile, std::ios::app);
    //m_outLogFile.open("log.txt", std::ios::app);
    if (m_outLogFile.is_open()) 
    {
        // Write the log message with timing to the file
        m_outLogFile << "[" << formattedTime << "] " << std::left << std::setw(20) << strLog << "| " << strMsg << "\n";
        m_outLogFile.close();
    }
    else 
    {
        std::cerr << "Failed to open the log file." << std::endl;
        return false;
    }

    return true;
}

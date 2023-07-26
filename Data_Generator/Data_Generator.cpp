#include <iostream>
#include "Include/include.h"
#include "CClient.h"

int main()
{

    std::cout << "Welcome to Data Generator!\n";
    //std::string strFile = "C:\\Users\\Asus\\Desktop\\Log\\order.txt";
    std::string strFile = R"(C:\Users\Asus\Desktop\Log\order.txt)";

    CClient cc1("127.0.0.1", 661);
    cc1.bClientCreate();
    std::cout << "Main Create!\n";

    /*std::cout << "Copy and paste the file path by right clicking on the text file (order.txt): ";
    std::cin >> strFile;*/

    //Open the file
    std::ifstream file(strFile);
    if (!file.is_open()) 
    {
        std::cout << "Failed to open file: " << strFile << std::endl;
        return false;
    }

    //Read the contents of the file into a vector
    std::vector<std::string> fileContent;
    std::string line;
    while (std::getline(file, line)) 
    {
        fileContent.push_back(line);
    }
    file.close();

    // Print the file content
    std::cout << "File Content:\n";
    int iCnt = 0;
    for (const std::string& str : fileContent) 
    {
        std::cout << ++iCnt << ". \t";
        std::cout << str << std::endl;
        cc1.bClientSend(str);
    }

    cc1.bClientClose();
    std::cout << "Main Close!\n";

    return 0;
}

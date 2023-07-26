#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <math.h>
#include <iomanip> // Include the <iomanip> header for std::setprecision
#include <vector>
#include <stdio.h>
#include <tchar.h>
#include <unordered_map>
#include <map>
//#include <format> //only for C++20
#include <sstream> // Include the <sstream> header for std::ostringstream

//print to log file
#include <fstream>

// limit
#include <limits.h> // for c
#include <climits>	// for cpp

// for max and min 
#include <algorithm>

// for socket
#include <Ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996) 
#ifdef _WIN32
	#include <WinSock2.h>
	typedef int socklen_t;
#else
	#include  <sys/socket.h>
#endif

#include <future> // For asynchorous threading


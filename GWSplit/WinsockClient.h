#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


enum e_WinsockCLientError {
	kWSAStartupFailed,
	kAddressLookupFailed,
	kInvalidSocket,
	kCannotConnectToServer
};

struct WinsockClientError {
	e_WinsockCLientError type;
	int code;
};

class WinsockClient
{
public:
	WinsockClient();

	int connect(LPCSTR ip, LPCSTR port, IPPROTO protocol = IPPROTO_TCP);
	int send(const char* data, int len);
	void disconnect();


private:
	WSADATA wsadata_		= { 0 };
	SOCKET socketconn_		= INVALID_SOCKET;

	PADDRINFOA result_		= nullptr;
	ADDRINFOA  hints_		= { 0 };

};
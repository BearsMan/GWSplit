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

WinsockClient::WinsockClient() {
	int result;

	result = WSAStartup(MAKEWORD(2, 2), &wsadata_);
	if (result) {
		throw WinsockClientError{ kWSAStartupFailed, result };
	}
}

int WinsockClient::connect(LPCSTR ip, LPCSTR port, IPPROTO protocol) {
	hints_.ai_family = AF_UNSPEC;
	hints_.ai_socktype = SOCK_STREAM;
	hints_.ai_protocol = protocol;

	int result;

	result = getaddrinfo(ip, port, &hints_, &result_);
	if (result != 0) {
		WSACleanup();
		return result;
	}

	for (PADDRINFOA idx = result_; idx != nullptr; idx = idx->ai_next) {
		socketconn_ = socket(idx->ai_family, idx->ai_socktype,
			idx->ai_protocol);

		if (socketconn_ == INVALID_SOCKET) {
			WSACleanup();
			return result;
		}

		result = ::connect(socketconn_, idx->ai_addr, (int)idx->ai_addrlen);
		if (result == SOCKET_ERROR) {
			closesocket(socketconn_);
			socketconn_ = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result_);

	if (socketconn_ == INVALID_SOCKET) {
		WSACleanup();
		return -1;
	}

	return 0;
}

int WinsockClient::send(const char * data, int len) {
	return ::send(socketconn_, data, len, 0);
}

void WinsockClient::disconnect() {
	shutdown(socketconn_, SD_BOTH);
	closesocket(socketconn_);
	WSACleanup();
}

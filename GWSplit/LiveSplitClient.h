#pragma once

#include "NamedPipeClient.h"



class LiveSplitClient : public NamedPipeClient
{
public:
	
	int connect() { return NamedPipeClient::connect("\\\\.\\pipe\\LiveSplit"); }

	void split() { send("split\r\n", sizeof("split\r\n")); }
	void start() { send("starttimer\r\n", sizeof("starttimer\r\n")); }
	void pause() { send("pause\r\n", sizeof("pause\r\n")); }
	void resume() { send("resume\r\n", sizeof("resume\r\n")); }
	void reset() { send("reset\r\n", sizeof("reset\r\n")); }
	void startorsplit() { send("startorsplit\r\n", sizeof("startorsplit\r\n")); }

};
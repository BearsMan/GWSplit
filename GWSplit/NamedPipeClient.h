#pragma once

#include <Windows.h>

enum e_NamedPipeClientError {
	kCannotFindClient,
	kPipeIsBusy,
	kPipeNotOpened,
	kStateNotChanged
};

class NamedPipeClient
{
public:

	int connect(LPCSTR pipename) {
		attempts_ = 0;
		strcpy_s(pipename_, pipename);
		while (attempts_++ < 20)
		{
			nphandle_ = CreateFileA(
				pipename_,   // pipe name 
				GENERIC_READ |  // read and write access 
				GENERIC_WRITE,
				FILE_SHARE_WRITE | FILE_SHARE_READ,
				NULL,           // default security attributes
				OPEN_EXISTING,  // opens existing pipe 
				0,              // default attributes 
				NULL);          // no template file 

								// Break if the pipe handle is valid. 

			if (nphandle_ != INVALID_HANDLE_VALUE)
				break;

			// Exit if an error other than ERROR_PIPE_BUSY occurs. 

			if (GetLastError() != ERROR_PIPE_BUSY)
			{
				return 1;
			}

			// All pipe instances are busy, so wait for 20 seconds. 

			if (!WaitNamedPipeA(pipename_, 20000)) {
				return 1;
			}


		}

		DWORD dwMode = PIPE_READMODE_BYTE;
		BOOL success = SetNamedPipeHandleState(
			nphandle_,    // pipe handle 
			&dwMode,  // new pipe mode 
			NULL,     // don't set maximum bytes 
			NULL);    // don't set maximum time 
		if (!success)
		{
			return kStateNotChanged;
		}

		return 0;
	}

	void disconnect() {
		CloseHandle(nphandle_);
	}


	BOOL send(void* data, int len) {
		return WriteFile(nphandle_, data, len, nullptr, nullptr);
	}

private:
	HANDLE nphandle_;
	int attempts_ = 0;
	char pipename_[MAX_PATH];
};
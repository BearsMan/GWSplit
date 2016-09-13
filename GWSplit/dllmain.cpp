// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "LiveSplitClient.h"

LiveSplitClient livesplit;

struct P023_ControlledCharacter {
	DWORD header;
	DWORD id;
	DWORD flag;
};

struct P0406_InitMapLoad {
	DWORD header;
	char pad[0x10];
	DWORD mapid;
};

template <typename T>
using StoChandler_t = bool(__fastcall*)(T* packet);

StoChandler_t<P023_ControlledCharacter> g__P023_original;
StoChandler_t<P0406_InitMapLoad>		g__P229_original;


bool __fastcall gwsplit_InitMapLoad(P0406_InitMapLoad* packet)
{
	printf("mapload start event occured.\n");
	livesplit.connect();
	livesplit.pause();
	livesplit.disconnect();
	return g__P229_original(packet);
}

bool __fastcall gwsplit_ControlledCharacter(P023_ControlledCharacter* packet)
{
	printf("mapload end event occured.\n");
	livesplit.connect();
	livesplit.resume();
	livesplit.disconnect();
	return g__P023_original(packet);
}

FILE* conhandle;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//AllocConsole();
		//freopen_s(&conhandle, "CONOUT$", "w", stdout);
		g__P229_original = (StoChandler_t<P0406_InitMapLoad>		)DetourFunc((BYTE*)0x007FF500, (BYTE*)gwsplit_InitMapLoad,			5);
		g__P023_original = (StoChandler_t<P023_ControlledCharacter>	)DetourFunc((BYTE*)0x005D3B73, (BYTE*)gwsplit_ControlledCharacter,	5);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		//fclose(conhandle);
		//FreeConsole();
		RetourFunc((BYTE*)0x007FF500, (BYTE*)g__P229_original, 5);
		RetourFunc((BYTE*)0x005D3B73, (BYTE*)g__P023_original, 5);
		livesplit.disconnect();
		break;
	}
	return TRUE;
}


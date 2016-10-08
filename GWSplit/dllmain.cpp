// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "LiveSplitClient.h"
#include <queue>
#include <vector>

LiveSplitClient livesplit;

typedef unsigned __int8 __uint8;
typedef unsigned __int16 __uint16;
typedef unsigned __int32 __uint32;

template < typename T>
class gw_array {
public:

	T index(__uint32 idx) {
		if (idx < 0 || idx >= size_cur_)
			return T();
		return arr_[idx];
	}

	T operator[](__uint32 idx) {
		return index(idx);
	}


	__uint32 size() const { return size_cur_; }
protected:
	T* arr_;
	__uint32 size_alloc_;
	__uint32 size_cur_;
};

struct Agent {
	__uint32* vtable;
	__uint8 unknown1[24];
	__uint8 unknown2[4]; //This actually points to the agent before but with a small offset
	Agent* NextAgent; //Pointer to the next agent (by id)
	__uint8 unknown3[8];
	__uint32 Id; //AgentId
	float Z; //Z coord in float
	float Width1;	//Width of the model's box
	float Height1;	//Height of the model's box
	float Width2;	//Width of the model's box (same as 1)
	float Height2;	//Height of the model's box (same as 1)
	float Width3;	//Width of the model's box (usually same as 1)
	float Height3;	//Height of the model's box (usually same as 1)
	float Rotation_angle; //Rotation in radians from East (-pi to pi)
	float Rotation_cos; // cosine of rotation
	float Rotation_sin; // sine of rotation
	__int32 NameProperties; //Bitmap basically telling what the agent is
	__uint8 unknown4[8];
	float unkfloat1;	// weird values, change with movement, always between -1 and 1
	float unkfloat2;
	float unkfloat3;
	__uint8 unknown5[4];
	struct {
		float X; //X coord in float
		float Y; //Y coord in float
		__uint32 Ground;
	};
	__uint8 unknown6[4];
	float NameTagX; //Exactly the same as X above
	float NameTagY; //Exactly the same as Y above
	float NameTagZ; //Z coord in float
	__uint8 unknown7[12];
	__int32 Type; //0xDB = players, npc's, monsters etc. 0x200 = signpost/chest/object (unclickable). 0x400 = item to pick up
	float MoveX; //If moving, how much on the X axis per second
	float MoveY; //If moving, how much on the Y axis per second
	__uint8 unknown8[4]; // always 0?
	float Rotation_cos2; // same as cosine above
	float Rotation_sin2; // same as sine above
	__uint8 unknown10[16];
	__int32 Owner;
	__uint32 itemid; // Only valid if agent is type 0x400 (item)
	__uint8 unknown24[4];
	__int32 ExtraType;
	__uint8 unknown11[24];
	float WeaponAttackSpeed; //The base attack speed in float of last attacks weapon. 1.33 = axe, sWORD, daggers etc.
	float AttackSpeedModifier; //Attack speed modifier of the last attack. 0.67 = 33% increase (1-.33)
	__uint16 PlayerNumber; //Selfexplanatory. All non-players have identifiers for their type. Two of the same mob = same number
	__uint8 unknown12[6];
	__uint32** Equip;
	__uint8 unknown13[10];
	__uint8 Primary; //Primary profession 0-10 (None,W,R,Mo,N,Me,E,A,Rt,P,D)
	__uint8 Secondary; //Secondary profession 0-10 (None,W,R,Mo,N,Me,E,A,Rt,P,D)
	__uint8 Level; //Duh!
	__uint8 TeamId; //0=None, 1=Blue, 2=Red, 3=Yellow
	__uint8 unknown14[14];
	float Energy; //Only works for yourself
	__int32 MaxEnergy; //Only works for yourself
	__uint8 unknown15[4];
	float HPPips; //Regen/degen as float
	__uint8 unknown16[4];
	float HP; //Health in % where 1=100% and 0=0%
	__int32 MaxHP; //Only works for yourself
	__int32 Effects; //Bitmap for effects to display when targetted. DOES include hexes
	__uint8 unknown17[4];
	__uint8 Hex; //Bitmap for the hex effect when targetted (apparently obsolete!) (yes)
	__uint8 unknown18[18];
	__int32 ModelState; //Different values for different states of the model.
	__int32 TypeMap; //Odd variable! 0x08 = dead, 0xC00 = boss, 0x40000 = spirit, 0x400000 = player
	__uint8 unknown19[16];
	__int32 InSpiritRange; //Tells if agent is within spirit range of you. Doesn't work anymore?
	__uint8 unknown20[16];
	__uint32 LoginNumber; //Unique number in instance that only works for players
	float AnimationSpeed;	// Speed of the current animation
	__uint8 AnimationUnk[4];	// related to animations
	__int32 AnimationID;		// Id of the current animation
	__uint8 unknown22[32];
	__uint8 DaggerStatus; // 0x1 = used lead attack, 0x2 = used offhand attack, 0x3 = used dual attack
	__uint8 Allegiance;  // 0x1 = ally/non-attackable, 0x2 = neutral, 0x3 = enemy, 0x4 = spirit/pet, 0x5 = minion, 0x6 = npc/minipet
	WORD WeaponType; //1=bow, 2=axe, 3=hammer, 4=daggers, 5=scythe, 6=spear, 7=sWORD, 10=wand, 12=staff, 14=staff
	WORD Skill;		//0 = not using a skill. Anything else is the Id of that skill
	WORD WeaponItemType;
	WORD OffhandItemType;
	WORD WeaponItemId;
	WORD OffhandItemId;

	// Health Bar Effect Bitmasks.
	inline bool GetIsBleeding() { return (Effects & 1) != 0; }
	inline bool GetIsConditioned() { return (Effects & 2) != 0; }
	inline bool GetIsDead() { return (Effects & 16) != 0; }
	inline bool GetIsDeepWounded() { return (Effects & 32) != 0; }
	inline bool GetIsPoisoned() { return (Effects & 64) != 0; }
	inline bool GetIsEnchanted() { return (Effects & 128) != 0; }
	inline bool GetIsDegenHexed() { return (Effects & 1024) != 0; }
	inline bool GetIsHexed() { return (Effects & 2048) != 0; }
	inline bool GetIsWeaponSpelled() { return (Effects & 32768) != 0; }

	// Agent Type Bitmasks.
	inline bool GetIsLivingType() { return (Type & 0xDB) != 0; }
	inline bool GetIsSignpostType() { return (Type & 0x200) != 0; }
	inline bool GetIsItemType() { return (Type & 0x400) != 0; }

	// Agent TypeMap Bitmasks.
	inline bool GetInCombatStance() { return (TypeMap & 0x1) != 0; }
	inline bool GetHasQuest() { return (TypeMap & 0x2) != 0; } // if agent has quest marker
	inline bool GetIsDeadByTypeMap() { return (TypeMap & 0x8) != 0; }
	inline bool GetIsFemale() { return (TypeMap & 0x200) != 0; }
	inline bool GetHasBossGlow() { return (TypeMap & 0x400) != 0; }
	inline bool GetIsHidingCape() { return (TypeMap & 0x1000) != 0; }
	inline bool GetCanBeViewedInPartyWindow() { return (TypeMap & 0x20000) != 0; }
	inline bool GetIsSpawned() { return (TypeMap & 0x40000) != 0; }
	inline bool GetIsBeingObserved() { return (TypeMap & 0x400000) != 0; }

	// Modelstates.
	inline bool GetIsKnockedDown() { return ModelState == 1104; }
	inline bool GetIsMoving() { return ModelState == 12 || ModelState == 76 || ModelState == 204; }
	inline bool GetIsAttacking() { return ModelState == 96 || ModelState == 1088 || ModelState == 1120; }

	inline bool IsPlayer() { return LoginNumber != 0; }
	inline bool IsNPC() { return LoginNumber == 0; }
};


struct P023_ControlledCharacter {
	__uint32 header;
	__uint32 id;
	__uint32 flag;
};

struct P0406_InitMapLoad {
	__uint32 header;
	__uint8 pad[0x10];
	__uint32 mapid;
};

template <typename T>
using StoChandler_t = bool(__fastcall*)(T* packet);

StoChandler_t<P023_ControlledCharacter> g__P023_original;
StoChandler_t<P0406_InitMapLoad>		g__P229_original;


enum e_Op {
	kPause,
	kResume,
	kSplit,
	kReset,
	kStart
};

std::queue<e_Op> g__commands;

// https://wiki.guildwars.com/wiki/Guild_Wars_Wiki:Game_integration
__uint32* mapidptr				= (__uint32*)0x00A31C50;
gw_array<Agent*>* agentarrayptr = (gw_array<Agent*>*)0x00D55A20;



bool inrun = false;
__uint32 lastmapid = 0;
__uint32 state = 0;
std::vector<bool(*)()> g__splits = {
	[]()-> bool { return lastmapid == 214 && *mapidptr == 251; },
	[]()-> bool { return lastmapid == 213 && *mapidptr == 250; },
	[]()-> bool { return lastmapid == 219 && *mapidptr == 273; },
	[]()-> bool { return lastmapid == 224 && *mapidptr == 279; },
	[]()-> bool { return lastmapid == 204 && *mapidptr == 277; },
	[]()-> bool { return lastmapid == 225 && *mapidptr == 226; },
	[]()-> bool { 
		auto& agents = *agentarrayptr;

		for (int i = 1; i < agents.size(); ++i) {
			auto agent = agents[i];
			if (agent == nullptr) continue;			// Agent exists?
			if (agent->PlayerNumber == 4119) {		// Agent is shiro?
				return agent->Effects & 0x10 > 0;	// Agent is dead?
			}
		}
		return false;
	}
};

DWORD WINAPI queueHandler(LPVOID arg) {
	while (1) {
		Sleep(1);

		//__try {

			if (g__commands.empty()) continue;

			e_Op op = g__commands.front();

			if (livesplit.connect()) {
				printf("Connect err: code %X\n", GetLastError());
				continue;
			}
			switch (op) {

			case kPause:
				livesplit.pause();
				printf("pause recieved\n");
				break;

			case kResume:
				printf("resume recieved\n");
				livesplit.resume();
				break;

			case kReset:
				printf("reset recieved\n");
				livesplit.reset();
				lastmapid = 0;
				state = 0;
				break;

			case kSplit:
				printf("split recieved\n");
				livesplit.split();
				state++;
				break;

			case kStart:
				printf("start recieved\n");
				livesplit.start();
				lastmapid = 0;
				state = 0;
				break;
			}

			g__commands.pop();
			livesplit.disconnect();
		//} __except(EXCEPTION_EXECUTE_HANDLER){}

	}
	return EXIT_SUCCESS;
}

DWORD WINAPI startHandler(LPVOID arg) {

	while (1) {
		while (*(void**)0xA2B2A0 == nullptr || agentarrayptr->size() == 0) {
			Sleep(10);
		}
		g__commands.push(kStart);
		while (*(void**)0xA2B2A0 != nullptr) {
			Sleep(10);
			if (g__splits[state]()) {
				g__commands.push(kSplit);
			}
		}
		g__commands.push(kReset);
	}
	return EXIT_SUCCESS;
}


bool __fastcall gwsplit_InitMapLoad(P0406_InitMapLoad* packet)
{
	printf("mapload start event occured.\n");
	lastmapid = *mapidptr;
	g__commands.push(e_Op::kPause);
	return g__P229_original(packet);
}

bool __fastcall gwsplit_ControlledCharacter(P023_ControlledCharacter* packet)
{
	printf("mapload end event occured.\n");
	g__commands.push(e_Op::kResume);
	return g__P023_original(packet);
}

FILE* conhandle;
HANDLE thread;
HANDLE startthread;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		freopen_s(&conhandle, "CONOUT$", "w", stdout);
		g__P229_original = (StoChandler_t<P0406_InitMapLoad>		)DetourFunc((__uint8*)0x007FF500, (__uint8*)gwsplit_InitMapLoad,			5);
		g__P023_original = (StoChandler_t<P023_ControlledCharacter>	)DetourFunc((__uint8*)0x005D3B73, (__uint8*)gwsplit_ControlledCharacter,	5);
		thread = CreateThread(0, 0, queueHandler, nullptr, 0, 0);
		startthread = CreateThread(0, 0, startHandler, nullptr, 0, 0);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		fclose(conhandle);
		FreeConsole();
		TerminateThread(startthread, EXIT_SUCCESS);
		TerminateThread(thread,		 EXIT_SUCCESS);
		RetourFunc((__uint8*)0x007FF500, (__uint8*)g__P229_original, 5);
		RetourFunc((__uint8*)0x005D3B73, (__uint8*)g__P023_original, 5);
		break;
	}
	return TRUE;
}


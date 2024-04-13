#pragma once
//#pragma warning(disable : 4996）
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "../utils/Logger.h"
#include "../config/ConfigManager.h"

// Define IL2CPP API function addresses
#define DO_API(a,r, n, p) r(*n) p
#include "il2cpp-api-functions.h"
#undef DO_API

// Define function addresses
#define DO_APP_FUNC(a,r, n, p) r(*n) p
#define DO_TYPEDEF(a, n) n ## __Class** n ## __TypeInfo
#define DO_APP_FUNC_METHODINFO(a, n) struct MethodInfo ** n
namespace app {
#include "il2cpp-types.h"
#include "il2cpp-functions.h"
}
#undef DO_APP_FUNC
#undef DO_TYPEDEF
#undef DO_APP_FUNC_METHODINFO

// Define UnityPlayer functions
#define DO_UP_FUNC(a,r, n, p) r(*n) p
namespace app {
#include "il2cpp-unityplayer-functions.h"
}
#undef DO_UP_FUNC

#define SELECT_VERSION(VERSION_VAR, a,b,c) (VERSION_VAR == GameVersion::TAIWAN ? a : VERSION_VAR == GameVersion::GLOBAL ? b : c)

enum class GameVersion {
	NONE,
	TAIWAN,
	GLOBAL,
	JAPAN,

};




GameVersion getGameVersion() {

	int version;
	LOG_WARNING("Please enter a number to select your game version");
	LOG_WARNING("\n TAIWAN : 1\n GLOBAL : 2 \n JAPAN : 3\n ");

	std::cin >> version;
	switch (version) {
	case 1: return GameVersion::TAIWAN;
	case 2: return GameVersion::GLOBAL;
	case 3: return GameVersion::JAPAN;
	default: return GameVersion::NONE;
	}
}

std::string gameVersionToString(GameVersion version) {
	switch (version) {
	case GameVersion::TAIWAN:
		return "TAIWAN";
	case GameVersion::GLOBAL:
		return "GLOBAL";
	case GameVersion::JAPAN:
		return "JAPAN";
	default:
		return "NONE";
	}
}
uintptr_t baseAddress;
uintptr_t unityPlayerAddress;

VOID init_il2cpp() {
	//auto gameVersion = getGameVersion();

	//if (gameVersion != GameVersion::NONE)
	//	LOG_WARNING("Selected version : %s",gameVersionToString(gameVersion).c_str());
	//else {
	//	LOG_ERROR("Unknown version, please contact the developer or update the software.");
	//	system("pause");
	//	exit(0);
	//	return;
	//}

	while (baseAddress == (uint64_t) nullptr) {
		Sleep(1000);
		baseAddress = (uint64_t)GetModuleHandleA("GameAssembly.dll");

		if (GetModuleHandleA("GameAssembly.dll") != nullptr) {
			baseAddress = (uint64_t)GetModuleHandleA("GameAssembly.dll");
			unityPlayerAddress = (uint64_t)GetModuleHandleA("UnityPlayer.dll");

			LOG_DEBUG("GameAssembly ptr: %p", baseAddress);
			LOG_DEBUG("UnityPlayer ptr: %p", unityPlayerAddress);


#define DO_API(a, r , n, p) n = (r (*) p)(baseAddress + a)
#include "il2cpp-api-functions.h"
#undef DO_API

#define DO_APP_FUNC(a, r, n, p) n = (r (*) p)(baseAddress + a)
#define DO_APP_FUNC_METHODINFO(a, n) n = (struct MethodInfo **)(baseAddress + a)
#include "il2cpp-functions.h"
#undef DO_APP_FUNC
#undef DO_APP_FUNC_METHODINFO

#define DO_TYPEDEF(a,  c, n) n ## __TypeInfo = (n ## __Class**) (baseAddress + a)
#include "il2cpp-types.h"
#undef DO_TYPEDEF

#define DO_UP_FUNC(a, r, n, p) n = (r (*) p)(unityPlayerAddress + a)
#include "il2cpp-unityplayer-functions.h"
#undef DO_UP_FUNC
		}
	}
}

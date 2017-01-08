#pragma once
#include <cpu.h>
#include <system.h>
enum Systems
{
	NES,
	GAMEBOY
};
CSystem * LoadSystem(enum Systems sys);


class CConfig {
public:
	bool realTimeDebug = false;
};


extern CSystem * g_running_system;
extern CConfig * g_config;

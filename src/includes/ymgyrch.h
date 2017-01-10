#pragma once
#include <cpu.h>
#include <system.h>
enum Systems
{
	NES,
	GAMEBOY,
	CHIP8
};
CSystem * LoadSystem(enum Systems sys);


class CConfig {
public:
	bool realTimeDebug = true;
	enum GUIMODE {
		NONE,
		TUI,
		LOG,
		GUI
	};
	GUIMODE displayMode;


	int tui_cols;
	int tui_rows;

};


extern CSystem * g_running_system;
extern CConfig * g_config;

#pragma once
#include <cpu.h>
#include <system.h>


/// All loadable systems
enum Systems
{
	NES,
	GAMEBOY,
	CHIP8
};

/// Creates a new instance of a system
EmuSystem * LoadSystem(enum Systems sys);


/// Emulator Config
class EmuConfig {
public:
	/// Debugger Enabled?
	bool realTimeDebug = true;

	///The GUI we're using
	enum GUIMODE {
		NONE,
		TUI,
		LOG,
		GUI
	};

	/// Current active GUI
	GUIMODE displayMode;

	///TUI: How many cols?
	int tui_cols;

	///TUI: How many rows.
	int tui_rows;

};


extern EmuSystem * g_running_system;
extern EmuConfig * g_config;

#pragma once
#include <cpu.h>
#include <system.h>
#include <log.h>

/// All loadable systems
enum Systems
{
	NES,
	GAMEBOY,
	CHIP8
};

/// Creates a new instance of a system
EmuSystem * LoadSystem(enum Systems sys);


typedef struct {
	int w;
	int h;
} tui_size_t;


/// Emulator Config
class EmuConfig {
public:
	enum GUIMODE {
		HEADLESS,
		TUI,
		GUI
	};

	struct {
		float runSpeed = 1.0000f;
		GUIMODE displayMode;
	} emulator;

	/// Debugging
	struct {
		
	} debug;

	/// TUI
	struct
	{
		int cols;
		int rows;
		int log_size;
		tui_size_t debugger_size;
		tui_size_t registers_size;
		bool showDebugger;
	} tui;

	/// Logging
	struct
	{
		bool logToStdio = false;
		bool logToFile = false;
		int logFilter = 0;
	} log;


};


extern EmuSystem * g_running_system;
extern EmuConfig * g_config;

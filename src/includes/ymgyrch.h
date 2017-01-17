#pragma once
#include <cpu.h>
#include <system.h>
#include <log.h>

/// All loadable systems

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

	enum Systems
	{
		UNKNOWN,
		NES,
		GAMEBOY,
		CHIP8
	};

	struct {
		float runSpeed = 1.0000f;
		GUIMODE displayMode;
		bool noGraphics = false;
		bool debugDefault = true;
		bool debuggerInline = true;
	} emulator;

	/// Debugging
	struct {
		unsigned int numToDissassemble = 10;
		bool dissassemblePast = false;
		unsigned int updateFrequency = 1;

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

/// Creates a new instance of a system
EmuSystem * LoadSystem(enum EmuConfig::Systems sys);


extern EmuConfig * g_config;

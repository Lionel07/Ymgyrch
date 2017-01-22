#pragma once
#include <cpu.h>
#include <system.h>
#include <log.h>

/// All loadable systems

namespace Ymgyrch {

	class Config {
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
	System * LoadSystem(enum Config::Systems sys);
	extern Config * config;

}
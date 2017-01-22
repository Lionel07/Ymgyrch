#include <log.h>
#include <ymgyrch.h>
#include <stdio.h>
#include <rlutil/rlutil.h>
#include <libfmt/fmt/format.h>
#include "tui.h"

EmuSystem * LoadSystem(enum Systems sys);
Systems toLoad;
char * romname;

void parseCmdline(char argc, char * argv[]) {
	bool foundRom = false;
	bool findingSystem = false;
	bool findingDebug = false;
	for (int i = 1; i < argc; i++)
	{
		if (findingSystem == true)
		{
			if (strcmp(argv[i], "gameboy") == 0) {
				toLoad = GAMEBOY;
			}
			if (strcmp(argv[i], "nes") == 0) {
				toLoad = NES;
			}
			if (strcmp(argv[i], "chip8") == 0) {
				toLoad = CHIP8;
			}
			findingSystem = false;
			continue;
		}

		if (findingDebug == true)
		{
			if (strcmp(argv[i], "true") == 0) {
				g_config->tui.showDebugger = true;
			}
			else
			{
				g_config->tui.showDebugger = false;
			}
			findingSystem = false;
			continue;
		}

		if (strcmp(argv[i], "-system") == 0) {
			findingSystem = true;
			continue;
		}
		if (strcmp(argv[i], "-debug") == 0) {
			findingDebug = true;
			continue;
		}
		if (strcmp(argv[i], "-pause") == 0) {
			g_tui->paused = true;
			continue;
		}


		// If anything else, we set the romname to this.
		romname = argv[i];
	}
}


int main(char argc, char * argv[]) {
	g_log = new Logger();
	g_config = new EmuConfig();
	g_tui = new TextUI();
	g_tui->Init();

	parseCmdline(argc, argv);

	g_running_system = LoadSystem(toLoad);
	g_log->Log("MAIN", "Loaded System: {}", g_running_system->name);

	// Start running system
	g_running_system->Init();
	g_running_system->LoadFile(romname);
	g_running_system->Start();
	

	while (g_running_system->isActive) {
		if (!g_tui->paused)
		{
			g_running_system->Tick();
		}
		if (g_tui->paused && g_tui->stepping) {
			g_tui->stepping = false;
			g_running_system->Tick();
		}

		g_tui->ProcessInput();
		g_tui->Update();
	}
	while (true)
	{
		g_tui->Update();
		char ret = rlutil::nb_getch();

		if (ret != 0)
		{
			break;
		}
	}
	
	return 0;
}

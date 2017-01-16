#include "emucore.h"

EmuCore::EmuCore()
{

}

void EmuCore::Init()
{
	running_system->Init();
	g_log->Log("MAIN", "Loaded System: {}", running_system->name);

	if (running_system->configNeedsRom) {
		running_system->LoadFile(image_location);
	}

}

void EmuCore::Start()
{
	running_system->Start();
}

void EmuCore::TickSystem()
{
	if (paused && !stepping) {
		return;
	}


	if (!running_system->isActive) {
		return;
	}

	running_system->Tick();
	stepping = false;
}

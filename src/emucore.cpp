#include "emucore.h"
#include <input.h>
Ymgyrch::Core::Core()
{
}

void Ymgyrch::Core::Init()
{
	running_system->Init();
	g_log->Log("Core", "Loaded System: {}", running_system->name);

	if (running_system->config.needsROMImage) {
		running_system->LoadFile(image_location);
	}
	if (running_system->config.needsGraphics) {
		running_system->gpu->sys = running_system;
	}
	Ymgyrch::input->Reset();
}

void Ymgyrch::Core::Start()
{
	running_system->Start();
}

void Ymgyrch::Core::TickSystem()
{
	if (paused && !stepping) {
		return;
	}

	if (!running_system->isActive) {
		return;
	}

	running_system->Tick();

	Ymgyrch::input->Update();

	stepping = false;
}
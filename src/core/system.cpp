#include <system.h>

void EmuSystem::Init()
{
	
}

void EmuSystem::Start()
{
	isActive = true;
}

void EmuSystem::Stop()
{
	isActive = false;
}

void EmuSystem::Reset()
{
	Stop();
}

void EmuSystem::LoadFile(std::string path)
{
}

void EmuSystem::Tick()
{
	if (!isActive)
	{
		return;
	}
}

EmuSystem::~EmuSystem()
{
}
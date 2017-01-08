#include <system.h>

void CSystem::Init()
{
	
}

void CSystem::Start()
{
	isActive = true;
}

void CSystem::Stop()
{
	isActive = false;
}

void CSystem::Reset()
{
	Stop();
}

void CSystem::LoadFile(std::string path)
{
}

void CSystem::Tick()
{
	if (!isActive)
	{
		return;
	}
}

CSystem::~CSystem()
{
}
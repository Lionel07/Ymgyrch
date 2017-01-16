#pragma once
#include <ymgyrch.h>
#include <vector>

class EmuCore
{
public:
	EmuSystem * running_system = nullptr;
	bool paused = false;
	bool stepping = false;

	EmuConfig::Systems system;
	std::string image_location = "";

    EmuCore();
	void Init();
	void Start();
	void TickSystem();
};

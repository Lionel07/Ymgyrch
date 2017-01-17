#pragma once
#include <string>

#include <system.h>
#include <cpu.h>
#include <device.h>

class EmuSystem;

class EmuGpu : public Device {
private:
	std::string name;
	bool isActive = true;
protected:
	EmuSystem * sys = nullptr;

public:

	virtual void Tick();
	virtual void Render();
	enum Backend {
		NONE,
		SDL
	};

	Backend backend = NONE;

};

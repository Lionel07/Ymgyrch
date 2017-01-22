#pragma once
#include <string>

#include <system.h>
#include <cpu.h>
#include <device.h>
#include <IVideoSystem.h>
namespace Ymgyrch {
	class System;
}


class EmuGpu : public Device {
private:
	std::string name;
	bool isActive = true;
public:
	Ymgyrch::System * sys = nullptr;
	IVideoSystem * subsys = nullptr;
public:
	virtual void Tick() = 0;
	virtual void Initialize() = 0;
	virtual void Render() = 0;
	virtual void Clear() = 0;
	virtual void Reset() = 0;

	enum Backend {
		NONE,
		SDL
	};

	Backend backend = NONE;

};

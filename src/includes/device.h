#pragma once
#include <string>

#include "system.h"
#include "cpu.h"


class EmuSystem;


class Device {

private:
	std::string name;
	bool isActive = false;

protected:
	EmuSystem * sys = nullptr;

public:
	virtual void Tick();

};

#pragma once
#include <string>

#include "system.h"
#include "cpu.h"

class System;

class Device {

private:
	std::string name;
	bool isActive = false;

protected:
	System * sys = nullptr;

public:
	virtual void Tick() = 0;

};

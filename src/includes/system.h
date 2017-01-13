#pragma once
#include <vector>
#include "cpu.h"
#include <memcontroller.h>
class Cpu; //Prototype


/*! An entire generic emulated system */
class EmuSystem {
public:
	/// The system's public name
	std::string name;
	/// Is the system active?
	bool isActive;

	/// All CPU's
	std::vector<Cpu*> cpu;

	/// The memory controller.
	MemoryController mem;

	/// Create inital system components
	virtual void Init();
	/// Start running the system
	virtual void Start();
	/// Stop running the system
    virtual void Stop();
	/// Runs every update. Updates all devices.
    virtual void Tick();
	/// Resets all devices
    virtual void Reset();
	/// Loads a file. Usually a ROM
	virtual void LoadFile(std::string path);

	EmuSystem::~EmuSystem();
};
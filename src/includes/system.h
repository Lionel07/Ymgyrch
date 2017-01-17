#pragma once
#include <vector>
#include <memcontroller.h>
#include <cpu.h>
#include <device.h>
#include <gpu.h>
class Cpu; //Prototype
class EmuGpu;
class Device;

/*! An entire generic emulated system */
class EmuSystem {
public:
	/// The system's public name
	std::string name;
	/// Is the system active?
	bool isActive;

	EmuGpu * gpu;

	/// Does this system need a rom
	bool configNeedsRom = true;

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
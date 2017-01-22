#pragma once
#include <vector>
#include <memcontroller.h>
#include <cpu.h>
#include <device.h>
#include <gpu.h>

class Cpu;
class EmuGpu;
class Device;

/*! An entire generic emulated system */


namespace Ymgyrch {
	class System {
	public:
		/// The system's public name
		std::string name;
		/// Is the system running
		bool isActive;
		struct system_config {
			bool needsROMImage = false;
			bool needsGraphics = false;
			bool needsSound = false;
			bool needsInput = false;

			int cpus = 0;
			int maxram = 0;


			bool needsSeperateClock;
			int seperateClockSpeed = 16;

		} config;

		std::vector<Cpu*> cpu;
		MemoryController mem;
		EmuGpu * gpu = nullptr;

		/// Create inital system components
		virtual void Init() = 0;
		/// Start running the system
		virtual void Start() = 0;
		/// Stop running the system
		virtual void Stop() = 0;
		/// Runs every update. Updates all devices.
		virtual void Tick() = 0;
		virtual void SubTick() = 0;
		/// Resets all devices
		virtual void Reset() = 0;
		/// Loads a file. Usually a ROM
		virtual void LoadFile(std::string path) = 0;
	};
}

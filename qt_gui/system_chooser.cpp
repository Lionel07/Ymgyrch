#include <ymgyrch.h>

#include <system/NES.h>
#include <system/Gameboy.h>
#include <system/CHIP8.h>

EmuSystem * LoadSystem(EmuConfig::Systems sys)
{
	switch (sys) {
	case EmuConfig::NES:
		return new System_Nes();
	case EmuConfig::GAMEBOY:
		return new System_Gameboy();
	case EmuConfig::CHIP8:
		return new System_Chip8();
	default:
		return nullptr;
	}
}
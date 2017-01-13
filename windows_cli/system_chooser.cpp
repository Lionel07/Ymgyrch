#include <ymgyrch.h>

#include <system/NES.h>
#include <system/Gameboy.h>
#include <system/CHIP8.h>

EmuSystem * g_running_system;

EmuSystem * LoadSystem(enum Systems sys)
{
	switch (sys) {
	case NES:
		return new System_Nes();
	case GAMEBOY:
		return new System_Gameboy();
	case CHIP8:
		return new System_Chip8();
	default:
		return nullptr;
	}
}
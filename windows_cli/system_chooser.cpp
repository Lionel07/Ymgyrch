#include <ymgyrch.h>

#include <system/NES.h>
#include <system/Gameboy.h>
#include <system/CHIP8.h>

CSystem * g_running_system;

CSystem * LoadSystem(enum Systems sys)
{
	switch (sys) {
	case NES:
		return new CSys_NES();
	case GAMEBOY:
		return new CSys_Gameboy();
	case CHIP8:
		return new CSys_Chip8();
	default:
		return nullptr;
	}
}
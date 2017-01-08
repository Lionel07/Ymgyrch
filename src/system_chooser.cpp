#include <ymgyrch.h>

#include <system/NES.h>

#include <system/Gameboy.h>

CSystem * g_running_system;

CSystem * LoadSystem(enum Systems sys)
{
	switch (sys) {
	case NES:
		return new CSys_NES();
	case GAMEBOY:
		return new CSys_Gameboy();
	default:
		return nullptr;
	}
}
#include <ymgyrch.h>

#include <system/Gameboy.h>
#include <system/CHIP8.h>

Ymgyrch::System * Ymgyrch::LoadSystem(Ymgyrch::Config::Systems sys)
{
	switch (sys) {
	case Ymgyrch::Config::GAMEBOY:
		return new System_Gameboy();
	case Ymgyrch::Config::CHIP8:
		return new System_Chip8();
	default:
		return nullptr;
	}
}
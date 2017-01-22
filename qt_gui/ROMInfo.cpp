#include <ROMInfo.h>
#include <ymgyrch.h>

Ymgyrch::Config::Systems YmgyrchUI::getSystemFromRom(std::string filename) {
	size_t isGB = filename.rfind(".gb");
	size_t isChip = filename.rfind(".ch8");
	size_t isNes = filename.rfind(".nes");

	if (isGB != std::string::npos) {
		return Ymgyrch::Config::GAMEBOY;
	}

	if (isChip != std::string::npos) {
		return Ymgyrch::Config::CHIP8;
	}

	if (isNes != std::string::npos) {
		return Ymgyrch::Config::NES;
	}

	return Ymgyrch::Config::UNKNOWN;
}
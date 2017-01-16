#include <ROMInfo.h>
#include <ymgyrch.h>


EmuConfig::Systems YmgyrchUI::getSystemFromRom(std::string filename) {

	size_t isGB = filename.rfind(".gb");
	size_t isChip = filename.rfind(".chip8");
	size_t isNes = filename.rfind(".nes");

	if (isGB != std::string::npos) {
		return EmuConfig::GAMEBOY;
	}

	if (isChip != std::string::npos) {
		return EmuConfig::CHIP8;
	}

	if (isNes != std::string::npos) {
		return EmuConfig::NES;
	}

	return EmuConfig::UNKNOWN;
}
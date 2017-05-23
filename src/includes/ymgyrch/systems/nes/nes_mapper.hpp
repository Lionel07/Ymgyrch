#pragma once

#include <ymgyrch/systems/nes/nes_mapper.hpp>

namespace Ymgyrch {
namespace Systems {
class NES;

namespace NES_Mappers {

typedef struct nes_rom {
	uint8_t * buffer;
	uint64_t buffer_sz;

	int rom_banks;
	int crom_banks;
	int ram_banks;
	uint8_t mapper;
	uint8_t flag_a;
	uint8_t flag_b;
} nes_rom_t;

class Mapper {
protected:
	Ymgyrch::Systems::NES * system;
	nes_rom_t * rom;
public:
	Mapper() {}
	Mapper(nes_rom_t * rom, Ymgyrch::Systems::NES * sys)
	{
		this->rom = rom;
		this->system = sys;
	}
	virtual void Init() = 0;
};
};
};
};

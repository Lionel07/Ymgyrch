#include <ymgyrch/systems/nes/nes_mapper.hpp>
#include <ymgyrch/systems/nes.hpp>

namespace Ymgyrch {
namespace Systems {
namespace NES_Mappers {
class NoMapper : public Mapper {
private:
	Memory::Device * cartROMA;
	Memory::Device * cartROMB;
public:
	NoMapper(nes_rom_t * rom, Ymgyrch::Systems::NES * sys)
	{
		this->rom = rom;
		this->system = sys;
	}
	void Init() {
		cartROMA = new Memory::RAM(0x4000);
		cartROMA->LoadData(rom->buffer, 0x4000);
		system->memController->Map(cartROMA, 0x8000);

		if (rom->rom_banks == 2) {
			cartROMB = new Memory::RAM(0x4000);
			cartROMB->LoadData(rom->buffer + 0x4000, 0x4000);
			system->memController->Map(cartROMB, 0xC000);
		}
		else {
			system->memController->Map(cartROMA, 0xC000);
		}
	};
};
};
};
};

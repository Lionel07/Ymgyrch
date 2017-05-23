#include <logging.hpp>
#include <ymgyrch/time.hpp>
#include <ymgyrch/state.hpp>
#include <ymgyrch/memory/ram.hpp>
#include <ymgyrch/cpu/2A03.hpp>
#include <ymgyrch/systems/nes.hpp>
#include <ymgyrch/systems/nes/nes_mapper.hpp>
#include <ymgyrch/systems/nes/nes_nomapper.hpp>

void Ymgyrch::Systems::NES::Init()
{
	name = "NES";
	memController = new Memory::Controller();
	cpus.push_back(new Cpus::CPU2A03());
	cpus[0]->Init(this);

	Memory::Device * internalRam = new Memory::RAM(0x800);
	memController->Map(internalRam, 0x0000);
	memController->Map(internalRam, 0x0800); // Mirror
	memController->Map(internalRam, 0x1000); // Mirror
	memController->Map(internalRam, 0x1800); // Mirror

	for (int i = 0; i < 0xFFFF; i++) {
		memController->WriteByte(i, 0x0);
	}
	g_log->Debug("NES", "Initialised");
	LoadRom();
}

void Ymgyrch::Systems::NES::LoadRom()
{
	const int header_offset = 16;
	FILE* file_rom = fopen(State::romImage.c_str(), "rb");
	if (file_rom) {
		fseek(file_rom, 0, SEEK_END);
		long fsize = ftell(file_rom);
		fseek(file_rom, 0, SEEK_SET);

		uint8_t * cartbuffer = new uint8_t[fsize];
		fread(cartbuffer, 1, fsize, file_rom);

		// Verify iNES header
		if (cartbuffer[0] == 0x4E &&
			cartbuffer[1] == 0x45 &&
			cartbuffer[2] == 0x53 &&
			cartbuffer[3] == 0x1A) {	
		}
		else {
			g_log->Log("NES", "ROM Bad.");
			fclose(file_rom);
			return;
		}

		// Load data from iNES header
		NES_Mappers::nes_rom_t * nes_rom = new NES_Mappers::nes_rom_t;
		nes_rom->buffer = cartbuffer + 16;
		nes_rom->buffer_sz = fsize;
		nes_rom->rom_banks = cartbuffer[4];
		nes_rom->crom_banks = cartbuffer[5];
		nes_rom->flag_a = cartbuffer[6];
		nes_rom->flag_b = cartbuffer[7];
		nes_rom->ram_banks = cartbuffer[8]; if (nes_rom->ram_banks == 0) nes_rom->ram_banks = 1;
		nes_rom->mapper = (nes_rom->flag_b << 4) | (nes_rom->flag_a & 0x8);

		g_log->Log("NES", "ROM Ok!");
		g_log->Log("NES", "ROM Path: {}", State::romImage);
		g_log->Log("NES", "ROM Size: 0x{0:X}", fsize - 16);
		g_log->Log("NES", "ROM Info: {} ({}k) ROM banks", nes_rom->rom_banks, nes_rom->rom_banks * 16);
		g_log->Log("NES", "ROM Info: {} ({}k) CROM banks", nes_rom->crom_banks, nes_rom->crom_banks * 8);
		g_log->Log("NES", "ROM Info: {} ({}k) RAM banks.", nes_rom->ram_banks, nes_rom->ram_banks * 8);
		g_log->Log("NES", "ROM Info: Mapper {}", nes_rom->mapper);

		if (nes_rom->mapper == 0) {
			cart = new NES_Mappers::NoMapper(nes_rom, this);
		}
		if (cart != nullptr) {
			cart->Init();
		}
		fclose(file_rom);
	}
}

void Ymgyrch::Systems::NES::Start()
{
	isActive = true;
	cpus[0]->Reset();
	g_log->Debug("NES", "Starting");
}

void Ymgyrch::Systems::NES::Stop()
{
	isActive = false;
	g_log->Debug("NES", "Stopping");
}

//#define SINGLE_STEP

void Ymgyrch::Systems::NES::Update()
{
	Cpus::CPU2A03 * cpu = static_cast<Cpus::CPU2A03*>(cpus[0]);
#ifndef SINGLE_STEP
	double dt = Time::getElapsed() - time;
	if (dt > 1.0) dt = 1.0; // Don't too much if we're behind. Slow down.

	int opTimeCPS = 1789773;
	double deltaCPS  = (double)opTimeCPS * dt; 
	int inc = 0;

	while (deltaCPS > cpu->registers.cyclesDelta) {
		cpu->Update();
		inc++;
	}
	cpu->registers.cyclesDelta = 0;
	time = Time::getElapsed();
	g_log->Debug("NES", "Did {} NES cycles in {} EOPS", deltaCPS, inc);
#else
	double dt = Time::getElapsed() - time;

	if (dt < 0.05) {
		return;
	}

	time = Time::getElapsed();
	cpu->Update();

#endif

}

void Ymgyrch::Systems::NES::Reset()
{
	cpus[0]->Reset();
	g_log->Debug("NES", "Reset");
}

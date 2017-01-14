#include <system/Gameboy.h>
#include <cpu/LR35902.h>
#include <log.h>
#include <mem/ram.h>
#include <mem/rom.h>
#include <mem/mirror_ram.h>
#include <mem/null_memory.h>

System_Gameboy::System_Gameboy() {
	this->name = "Gameboy";
}

void System_Gameboy::Init() {
	Cpu * cpu0 = new CPU_LR35902(this);
	cpu.push_back(cpu0);

	mem.SetAddressSpace(0xFFFF);

	Memory_RAM * wram0 = new Memory_RAM(0x2000, "WRAM0");
	Memory_MirrorRAM * weram0 = new Memory_MirrorRAM(wram0,"ECHO0", 0x1E00);
	Memory_MappedNull * hires = new Memory_MappedNull(0x60, "RESRV");
	Memory_RAM * mmio0 = new Memory_RAM(0x80, "MMIO0");
	Memory_RAM * hram0 = new Memory_RAM(0x7F, "HRAM0");
	Memory_RAM * mintr = new Memory_RAM(0x01, "MINTR");
	wram0->littleEndian = false;
	weram0->littleEndian = false;
	hires->littleEndian = false;
	mmio0->littleEndian = false;
	mintr->littleEndian = false;
	mem.Map(wram0, 0xC000);
	mem.Map(weram0, 0xE000);
	mem.Map(hires, 0xFEA0);
	mem.Map(mmio0, 0xFF00);
	mem.Map(hram0, 0xFF80);
	mem.Map(mintr, 0xFFFF);
	cpu0->Init();
	
}

void System_Gameboy::Start() {
	isActive = true;
	mem.DebugPrintMemoryMap();
	g_log->Log("GB", "Starting!");
}

void System_Gameboy::Stop() {
	isActive = false;
}

void System_Gameboy::Tick() {
	if (!isActive) { return; }
	for each (Cpu * processor in cpu) {
		processor->Tick();
	}
}

void System_Gameboy::Reset() {
	for each (Cpu * cur in cpu)
	{
		delete cur;
	}
	cpu.clear();
	Init();
}

void System_Gameboy::LoadFile(std::string path) {
	g_log->Log("GB", "Inserting Cart");

	FILE* rom = fopen(path.c_str(), "rb");
	if (rom) { 
		fseek(rom, 0, SEEK_END);
		long fsize = ftell(rom);
		fseek(rom, 0, SEEK_SET);

		uint8_t * cartbuffer = new uint8_t[fsize];
		fread(cartbuffer, 1, fsize, rom);

		g_log->Log("GB", "ROM Size: 0x{0:X}", fsize);
		g_log->Log("GB", "ROM Name: {0:s}", &cartbuffer[0x134]);

		int romnum = 0;
		uint64_t cart_size = fsize;
		for (cart_size = fsize; cart_size > 0; cart_size -= 0x4000)
		{
			char buffer[50];
			sprintf(buffer, "CARTROM%d", romnum);

			Memory_ROM * cartrom = new Memory_ROM(0x4000, buffer);
			cartrom->littleEndian = false;
			cartrom->LoadData(&cartbuffer[fsize - cart_size], 0x4000);

			// Map the first 2 banks
			if (romnum < 2) {
				mem.Map(cartrom, fsize - cart_size);
			}

			romnum++;
		}
		fclose(rom);
	}
	else
	{
		g_log->Error("GB", "Failed to open rom {0:s}", path.c_str());
		Stop();
	}
	
	
}
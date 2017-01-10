#include <system/CHIP8.h>
#include <cpu/CHIP8Cpu.h>
#include <log.h>
#include <mem/ram.h>
#include <mem/mirror_ram.h>
CSys_Chip8::CSys_Chip8() {
	this->name = "Chip 8";
}

void CSys_Chip8::Init() {
	cpu.push_back(new CCpu_Chip8(this));

	CMem_RAM * memoryspace = new CMem_RAM(0x1000, "WRAM0");
	memoryspace->littleEndian = true;
	mem.Map(memoryspace, 0);
	cpu[0]->Init();
	g_log->Log("CHIP8", "Initialised");
}

void CSys_Chip8::Start()
{
	isActive = true;
}

void CSys_Chip8::Stop()
{
	isActive = false;
}

void CSys_Chip8::Tick() {
	for each (CCpu * processor in cpu) {
		processor->Tick();
	}
}

void CSys_Chip8::Reset()
{
	cpu.clear();
	Init();
}


void CSys_Chip8::LoadFile(std::string path) {
	g_log->Log("CHIP8", "Loading ROM {}", path);

	FILE* rom = fopen(path.c_str(), "rb");
	if (rom) {
		fseek(rom, 0, SEEK_END);
		long fsize = ftell(rom);
		fseek(rom, 0, SEEK_SET);

		uint8_t * cartbuffer = new uint8_t[fsize];
		fread(cartbuffer, 1, fsize, rom);

		if (fsize > 0xE00)
		{
			fsize = 0xE00;
		}
		CMem_RAM * memory = (CMem_RAM*)mem.GetDeviceForAddress(0x0)->dev;
		memory->LoadData(cartbuffer, fsize, 0x200);
		fclose(rom);
	}
	else
	{
		g_log->Log("CHIP8", "Failed to open rom {0:s}", path.c_str());
		Stop();
	}


}
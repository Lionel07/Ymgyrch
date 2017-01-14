#include <system/NES.h>
#include <cpu/6502.h>
#include <log.h>
#include <mem/ram.h>
#include <mem/mirror_ram.h>
System_Nes::System_Nes() {
	this->name = "Nintendo Entertainment System";
}

void System_Nes::Init() {
	
	Cpu * cpu0 = new CPU_6502(this, CPU_6502::MODEL_2A03);
	cpu.push_back(cpu0);
	
	mem.SetAddressSpace(0xFFFF);

	Memory_RAM * wram = new Memory_RAM(0x800, "RAM");
	Memory_MirrorRAM * mram0 = new Memory_MirrorRAM(wram, "MRAM0");
	Memory_MirrorRAM * mram1 = new Memory_MirrorRAM(wram, "MRAM1");
	Memory_MirrorRAM * mram2 = new Memory_MirrorRAM(wram, "MRAM2");
	wram->littleEndian = true;
	mem.Map(wram , 0x0000);
	mem.Map(mram0, 0x0800);
	mem.Map(mram1, 0x1000);
	mem.Map(mram2, 0x1800);

	cpu0->Init();
}

void System_Nes::Start()
{
	isActive = true;
	mem.DebugPrintMemoryMap();
	g_log->Log("NES", "Starting!");
}

void System_Nes::Stop()
{
	isActive = false;
}

void System_Nes::Tick() {
	for each (Cpu * processor in cpu) {
		processor->Tick();
	}
}

void System_Nes::Reset()
{
	cpu.clear();
	Init();
}

void System_Nes::LoadFile(std::string path) {
	g_log->Log("NES", "Loading: {}", path);
	
	FILE* rom = fopen(path.c_str(), "rb");
	if (rom) {
		///@todo Determine rom type here. We just assume iNES right now.
		LoadINESRom(rom);
		fclose(rom);
	}
	else
	{
		g_log->Error("NES", "Failed to open rom {0:s}", path.c_str());
		Stop();
	}
}

void System_Nes::LoadINESRom(FILE * rom) {
	uint8_t buffer[16];
	uint8_t * romdat;
	fread(buffer, 1, 16, rom);
	
	// Verify that this is an iNes rom.

	if (!(buffer[0] == 'N' && buffer[1] == 'E' && buffer[2] == 'S')) {
		g_log->Error("NES", "ROM is not an iNES rom.");
		Stop();
		return;
	}

	g_log->Log("NES", "Program Size: {}kb", buffer[4] * 16);
	g_log->Log("NES", "Character Rom: {}kb", buffer[5] * 8);
	g_log->Log("NES", "RAM: {}kb", buffer[8] * 8);
	g_log->Log("NES", "Mapper: {0:08b}", buffer[6]);


	if (buffer[6] == 0) {
		//Load with mapper 0
		romdat = new uint8_t[0x4000 * buffer[4]];
		fread(romdat, 1, 0x4000 * buffer[4], rom);


		Memory_RAM * nrom0 = new Memory_RAM(0x4000, "NROM0");
		nrom0->LoadData(romdat + 0, 0x4000);
		mem.Map(nrom0, 0x8000);

		if (buffer[4] > 1) {
			Memory_RAM * nrom1 = new Memory_RAM(0x4000, "NROM1");
			nrom1->LoadData(romdat + 0x4000, 0x4000);
			mem.Map(nrom1, 0xC000);
		}
		else {
			Memory_MirrorRAM * nrommirror = new Memory_MirrorRAM(nrom0, "NROM0_M");
			mem.Map(nrommirror, 0xC000);
		}
	}
}
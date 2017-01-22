#include <system/CHIP8.h>
#include <cpu/CHIP8Cpu.h>
#include <log.h>
#include <mem/ram.h>
#include <mem/mirror_ram.h>
#include <input.h>
System_Chip8::System_Chip8() {
	this->name = "Chip 8";
}

System_Chip8::~System_Chip8() {
	delete gpu;
	for each (Cpu * processor in cpu) {
		delete processor;
	}
}

void System_Chip8::Init() {
	cpu.push_back(new CPU_Chip8(this));

	Memory_RAM * memoryspace = new Memory_RAM(0x1000, "WRAM0");
	memoryspace->littleEndian = true;
	mem.Map(memoryspace, 0);
	gpu = new Chip8GPU();
	cpu[0]->Init();
	g_log->Log("CHIP8", "Initialized");
	memoryspace->LoadData(chip8_fontset, 80, 0);

	config.cpus = 1;
	config.maxram = 0xFFF;
	config.needsGraphics = true;
	config.needsInput = true;
	config.needsROMImage = true;
	config.needsSound = true;

	config.needsSeperateClock = true;
	config.seperateClockSpeed = 16;
}

void System_Chip8::Start()
{
	isActive = true;
	Ymgyrch::input->mapNewKey("0", 0x58);
	Ymgyrch::input->mapNewKey("1", 0x31);
	Ymgyrch::input->mapNewKey("2", 0x32);
	Ymgyrch::input->mapNewKey("3", 0x33);
	Ymgyrch::input->mapNewKey("4", 0x51);
	Ymgyrch::input->mapNewKey("5", 0x57);
	Ymgyrch::input->mapNewKey("6", 0x45);
	Ymgyrch::input->mapNewKey("7", 0x41);
	Ymgyrch::input->mapNewKey("8", 0x53);
	Ymgyrch::input->mapNewKey("9", 0x44);
	Ymgyrch::input->mapNewKey("A", 0x5a);
	Ymgyrch::input->mapNewKey("B", 0x43);
	Ymgyrch::input->mapNewKey("C", 0x34);
	Ymgyrch::input->mapNewKey("D", 0x52);
	Ymgyrch::input->mapNewKey("E", 0x46);
	Ymgyrch::input->mapNewKey("F", 0x56);
}

void System_Chip8::Stop()
{
	isActive = false;
}

void System_Chip8::Tick() {
	for each (Cpu * processor in cpu) {
		processor->Tick();
	}
	gpu->Render();
}

void System_Chip8::SubTick() {
	for each (CPU_Chip8 * processor in cpu) {
		if (processor->regs.timer_delay > 0) {
			processor->regs.timer_delay--;
		}
	}
}

void System_Chip8::Reset()
{
	cpu.clear();
	Init();
}

void System_Chip8::LoadFile(std::string path) {
	g_log->Log("CHIP8", "Loading ROM {}", path);

	FILE* rom = fopen(path.c_str(), "rb");
	if (rom) {
		fseek(rom, 0, SEEK_END);
		long fsize = ftell(rom);
		fseek(rom, 0, SEEK_SET);

		uint8_t * cartbuffer = new uint8_t[fsize];
		fread(cartbuffer, 1, fsize, rom);
		if (fsize > 0xE00) {
			fsize = 0xE00;
		}
		Memory_RAM * memory = (Memory_RAM*)mem.GetDeviceForAddress(0x0)->dev;
		memory->LoadData(cartbuffer, fsize, 0x200);
		fclose(rom);
	}
	else {
		g_log->Log("CHIP8", "Failed to open rom {0:s}", path.c_str());
		Stop();
	}
}
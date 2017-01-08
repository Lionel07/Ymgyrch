#include <system/NES.h>
#include <cpu/6502.h>
#include <log.h>
#include <mem/ram.h>
#include <mem/mirror_ram.h>
CSys_NES::CSys_NES() {
	this->name = "Nintendo Entertainment System";
}

void CSys_NES::Init() {
	CCpu * cpu0 = new CCpu_6502(this);
//	CMemory * ram0 = new CMem_RAM(0x0800, "WRAM0");
//	CMemory * mram0 = new CMem_MirrorRAM(ram0, "MRAM0");
//	CMemory * mram1 = new CMem_MirrorRAM(ram0, "MRAM1");
//	CMemory * mram2 = new CMem_MirrorRAM(ram0, "MRAM2");

	cpu.push_back(cpu0);
	cpu0->Init();


	g_log->Log("NES", "Initialised");
}

void CSys_NES::Start()
{
	isActive = true;
}

void CSys_NES::Stop()
{
	isActive = false;
}

void CSys_NES::Tick() {
	for each (CCpu * processor in cpu) {
		processor->Tick();
	}
}

void CSys_NES::Reset()
{
	cpu.clear();
	Init();
}
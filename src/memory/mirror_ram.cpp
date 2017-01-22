#include <mem/ram.h>
#include <mem/mirror_ram.h>
#include <cstring>
#include <log.h>

Memory_MirrorRAM::Memory_MirrorRAM(Memory * mirror, std::string name) {
	this->mirror = mirror;
	this->name = name;
	mem_size = mirror->GetSize();
	//g_log->Log(this->name.c_str(), "Mirror RAM bank created (size 0x%X)", mem_size);
}

Memory_MirrorRAM::Memory_MirrorRAM(Memory * mirror, std::string name, uint64_t memsz)
{
	this->mirror = mirror;
	this->name = name;
	mem_size = memsz;
	//g_log->Log(this->name.c_str(), "Mirror RAM bank created (size 0x%X)", mem_size);
}

uint8_t Memory_MirrorRAM::ReadByte(uint64_t address)
{
	return mirror->ReadByte(address);
}

uint16_t Memory_MirrorRAM::ReadShort(uint64_t address)
{
	return mirror->ReadShort(address);
}

uint32_t Memory_MirrorRAM::ReadWord(uint64_t address)
{
	return mirror->ReadWord(address);
}

uint64_t Memory_MirrorRAM::ReadLong(uint64_t address)
{
	return mirror->ReadLong(address);
}

void Memory_MirrorRAM::WriteByte(uint64_t address, uint8_t data)
{
	mirror->WriteByte(address, data);
}

void Memory_MirrorRAM::WriteShort(uint64_t address, uint16_t data)
{
	mirror->WriteShort(address, data);
}

void Memory_MirrorRAM::WriteWord(uint64_t address, uint32_t data)
{
	mirror->WriteWord(address, data);
}

void Memory_MirrorRAM::WriteLong(uint64_t address, uint64_t data)
{
	mirror->WriteLong(address, data);
}

uint64_t Memory_MirrorRAM::GetSize()
{
	return mem_size;
}

void Memory_MirrorRAM::LoadData(uint8_t * buffer, uint64_t sz) {
	mirror->LoadData(buffer, sz);
}
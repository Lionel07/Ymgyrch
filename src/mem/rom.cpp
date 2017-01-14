#include <mem/rom.h>
#include <cstring>
#include <log.h>
#include <host.h>

Memory_ROM::Memory_ROM(uint64_t size) {
	mem_size = size;
	memory = new uint8_t[size];
	//g_log->Log("MEM", "Unnamed ROM bank created (size 0x%X)", size);
}

Memory_ROM::~Memory_ROM()
{
	delete[] memory;
}

Memory_ROM::Memory_ROM(uint64_t size, std::string name) {
	mem_size = size;
	memory = new uint8_t [size];
	this->name = name;
	//g_log->Log(this->name.c_str(), "ROM bank created (size 0x%X)", size);
}


uint8_t Memory_ROM::ReadByte(uint64_t address)
{
	if (address > mem_size) { return 0; }
	return memory[address];
}

uint16_t Memory_ROM::ReadShort(uint64_t address)
{
	uint8_t a;
	uint8_t b;

	if (littleEndian) {
		a = ReadByte(address);
		b = ReadByte(address + 1);
	}
	else {
		a = ReadByte(address + 1);
		b = ReadByte(address);
	}

	uint16_t ret = (uint16_t)((a << 8) | (b & 0xff));
	return ret;
}

uint32_t Memory_ROM::ReadWord(uint64_t address)
{
	uint16_t b = ReadShort(address);
	uint16_t a = ReadShort(address + 2);
	
	return (uint32_t)((a << 16) | (b & 0xffff));
}

uint64_t Memory_ROM::ReadLong(uint64_t address)
{
	uint32_t b = ReadWord(address);
	uint32_t a = ReadWord(address + 2);

	return (uint64_t)((a << 16) | (b & 0xffffffff)); ///@todo Fix this so that it actually returns a proper 64 bit number
}



void Memory_ROM::WriteByte(uint64_t address, uint8_t data) {}
void Memory_ROM::WriteShort(uint64_t address, uint16_t data) {}
void Memory_ROM::WriteWord(uint64_t address, uint32_t data) {}
void Memory_ROM::WriteLong(uint64_t address, uint64_t data) {}

uint64_t Memory_ROM::GetSize()
{
	return mem_size;
}

void Memory_ROM::LoadData(uint8_t * buffer, uint64_t sz)
{
	uint64_t maxsz = mem_size;
	if (sz < maxsz) {
		maxsz = sz;
	}

	memcpy(this->memory, buffer, maxsz);
}

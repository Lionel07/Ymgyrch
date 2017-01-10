#include <mem/rom.h>
#include <cstring>
#include <log.h>
#include <host.h>

CMem_ROM::CMem_ROM(uint64_t size) {
	mem_size = size;
	memory = new uint8_t[size];
	//g_log->Log("MEM", "Unnamed ROM bank created (size 0x%X)", size);
}

CMem_ROM::~CMem_ROM()
{
	delete[] memory;
}

CMem_ROM::CMem_ROM(uint64_t size, std::string name) {
	mem_size = size;
	memory = new uint8_t [size];
	this->name = name;
	//g_log->Log(this->name.c_str(), "ROM bank created (size 0x%X)", size);
}


uint8_t CMem_ROM::ReadByte(uint64_t address)
{
	if (address > mem_size) { return 0; }
	return memory[address];
}

uint16_t CMem_ROM::ReadShort(uint64_t address)
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

uint32_t CMem_ROM::ReadWord(uint64_t address)
{
	uint16_t b = ReadShort(address);
	uint16_t a = ReadShort(address + 2);
	
	return (uint32_t)((a << 16) | (b & 0xffff));
}

uint64_t CMem_ROM::ReadLong(uint64_t address)
{
	uint32_t b = ReadWord(address);
	uint32_t a = ReadWord(address + 2);

	return (uint64_t)((a << 16) | (b & 0xffffffff)); //Todo fix
}



void CMem_ROM::WriteByte(uint64_t address, uint8_t data) {}
void CMem_ROM::WriteShort(uint64_t address, uint16_t data) {}
void CMem_ROM::WriteWord(uint64_t address, uint32_t data) {}
void CMem_ROM::WriteLong(uint64_t address, uint64_t data) {}

uint64_t CMem_ROM::GetSize()
{
	return mem_size;
}

void CMem_ROM::LoadData(uint8_t * buffer, uint64_t sz)
{
	uint64_t maxsz = mem_size;
	if (sz < maxsz) {
		maxsz = sz;
	}

	memcpy(this->memory, buffer, maxsz);
}

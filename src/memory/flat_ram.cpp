#include <mem/ram.h>
#include <cstring>
#include <log.h>

Memory_RAM::Memory_RAM() {
}

Memory_RAM::Memory_RAM(uint64_t size) {
	mem_size = size;
	memory = new uint8_t[mem_size];
	memset(memory, 0, size);
	//g_log->Log("MEM", "Unnamed RAM bank created (size 0x%X)", size);
}

Memory_RAM::Memory_RAM(uint64_t size, std::string name) {
	mem_size = size;
	memory = new uint8_t[(size_t)mem_size];
	this->name = name;
	memset(memory, 0, mem_size);
	//g_log->Log(this->name.c_str(), "RAM bank created (size 0x%X)", size);
}

Memory_RAM::~Memory_RAM()
{
	delete[] memory;
}

uint8_t Memory_RAM::ReadByte(uint64_t address) {
	if (address > mem_size) { return 0; }
	return memory[address];
}

uint16_t Memory_RAM::ReadShort(uint64_t address) {
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

uint32_t Memory_RAM::ReadWord(uint64_t address) {
	uint16_t b = ReadShort(address);
	uint16_t a = ReadShort(address + 2);
	return (uint32_t)((a << 16) | (b & 0xffff));
}

uint64_t Memory_RAM::ReadLong(uint64_t address) {
	uint32_t b = ReadWord(address);
	uint32_t a = ReadWord(address + 2);
	return (uint64_t)((a << 16) | (b & 0xffffffff));
}

void Memory_RAM::WriteByte(uint64_t address, uint8_t data) {
	if (address > mem_size) { return; }
	memory[address] = data;
}

void Memory_RAM::WriteShort(uint64_t address, uint16_t data) {
	WriteByte(address, (unsigned char)(data & 0x00ff));
	WriteByte(address + 1, (unsigned char)((data & 0xff00) >> 8));
}

void Memory_RAM::WriteWord(uint64_t address, uint32_t data) {
	WriteShort(address, (unsigned char)(data & 0x0000ffff));
	WriteShort(address + 2, (unsigned char)((data & 0xffff0000) >> 16));
}

void Memory_RAM::WriteLong(uint64_t address, uint64_t data) {
	if (address > mem_size) { return; }
	///@todo: Implement long support
}

uint64_t Memory_RAM::GetSize() {
	return mem_size;
}

void Memory_RAM::LoadData(uint8_t * buffer, uint64_t sz)
{
	uint64_t maxsz = mem_size;
	if (sz < maxsz) {
		maxsz = sz;
	}

	memcpy(this->memory, buffer, maxsz);
}

void Memory_RAM::LoadData(uint8_t * buffer, uint64_t sz, uint64_t offset)
{
	uint64_t maxsz = mem_size;
	if (sz < maxsz) {
		maxsz = sz;
	}

	memcpy(this->memory + offset, buffer, maxsz);
}
#include <mem/ram.h>
#include <cstring>
#include <log.h>

CMem_RAM::CMem_RAM() {
}

CMem_RAM::CMem_RAM(uint64_t size) {
	mem_size = size;
	memory = new uint8_t[mem_size];
	memset(memory, 0, size);
	//g_log->Log("MEM", "Unnamed RAM bank created (size 0x%X)", size);
}

CMem_RAM::CMem_RAM(uint64_t size, std::string name) {
	mem_size = size;
	memory = new uint8_t[(size_t)mem_size];
	this->name = name;
	memset(memory, 0, mem_size);
	//g_log->Log(this->name.c_str(), "RAM bank created (size 0x%X)", size);
}

CMem_RAM::~CMem_RAM()
{
	delete[] memory;
}

uint8_t CMem_RAM::ReadByte(uint64_t address) {
	if (address > mem_size) { return 0; }
	return memory[address];
}

uint16_t CMem_RAM::ReadShort(uint64_t address) {
	uint8_t b = ReadByte(address);
	uint8_t a = ReadByte(address + 1);
	return (uint16_t)((a << 8) | (b & 0xff));
}

uint32_t CMem_RAM::ReadWord(uint64_t address) {
	uint16_t b = ReadShort(address);
	uint16_t a = ReadShort(address + 2);
	return (uint32_t)((a << 16) | (b & 0xffff));
}

uint64_t CMem_RAM::ReadLong(uint64_t address) {
	uint32_t b = ReadWord(address);
	uint32_t a = ReadWord(address + 2);
	return (uint64_t)((a << 16) | (b & 0xffffffff));
}

void CMem_RAM::WriteByte(uint64_t address, uint8_t data) {
	if (address > mem_size) { return; }
	memory[address] = data;
}

void CMem_RAM::WriteShort(uint64_t address, uint16_t data) {
	WriteByte(address, (unsigned char)(data & 0x00ff));
	WriteByte(address + 1, (unsigned char)((data & 0xff00) >> 8));
}

void CMem_RAM::WriteWord(uint64_t address, uint32_t data) {
	if (address > mem_size) { return; }
	memory[address] = data;
}

void CMem_RAM::WriteLong(uint64_t address, uint64_t data) {
	if (address > mem_size) { return; }
	memory[address] = data;
}

uint64_t CMem_RAM::GetSize() {
	return mem_size;
}

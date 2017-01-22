#include <mem/null_memory.h>
#include <cstring>
#include <log.h>

Memory_MappedNull::Memory_MappedNull(uint64_t size) {
	mem_size = size;
}

Memory_MappedNull::Memory_MappedNull(uint64_t size, std::string name) {
	mem_size = size;
	this->name = name;
}

uint8_t Memory_MappedNull::ReadByte(uint64_t address) {
	return 0;
}

uint16_t Memory_MappedNull::ReadShort(uint64_t address) {
	return 0;
}

uint32_t Memory_MappedNull::ReadWord(uint64_t address) {
	return 0;
}

uint64_t Memory_MappedNull::ReadLong(uint64_t address) {
	return 0;
}

void Memory_MappedNull::WriteByte(uint64_t address, uint8_t data) {
}

void Memory_MappedNull::WriteShort(uint64_t address, uint16_t data) {
}

void Memory_MappedNull::WriteWord(uint64_t address, uint32_t data) {
}

void Memory_MappedNull::WriteLong(uint64_t address, uint64_t data) {
}

uint64_t Memory_MappedNull::GetSize() {
	return mem_size;
}

void Memory_MappedNull::LoadData(uint8_t * buffer, uint64_t sz) {
}
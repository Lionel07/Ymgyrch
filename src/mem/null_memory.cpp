#include <mem/null_memory.h>
#include <cstring>
#include <log.h>

CMem_Null::CMem_Null(uint64_t size) {
	mem_size = size;
}

CMem_Null::CMem_Null(uint64_t size, std::string name) {
	mem_size = size;
	this->name = name;
}

uint8_t CMem_Null::ReadByte(uint64_t address) {
	return 0;
}

uint16_t CMem_Null::ReadShort(uint64_t address) {
	return 0;
}

uint32_t CMem_Null::ReadWord(uint64_t address) {
	return 0;
}

uint64_t CMem_Null::ReadLong(uint64_t address) {
	return 0;
}

void CMem_Null::WriteByte(uint64_t address, uint8_t data) {
}

void CMem_Null::WriteShort(uint64_t address, uint16_t data) {
}

void CMem_Null::WriteWord(uint64_t address, uint32_t data) {
}

void CMem_Null::WriteLong(uint64_t address, uint64_t data) {
}

uint64_t CMem_Null::GetSize() {
	return mem_size;
}

void CMem_Null::LoadData(uint8_t * buffer, uint64_t sz) {

}

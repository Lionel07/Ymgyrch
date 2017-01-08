#pragma once
#include <memory.h>
class CMem_Null : public CMemory {
private:
	uint64_t mem_size = 0;
public:
	explicit CMem_Null(uint64_t size);
	explicit CMem_Null(uint64_t size, std::string name);

	uint8_t  ReadByte(uint64_t address);
	uint16_t ReadShort(uint64_t address);
	uint32_t ReadWord(uint64_t address);
	uint64_t ReadLong(uint64_t address);

	void WriteByte(uint64_t address, uint8_t  data);
	void WriteShort(uint64_t address, uint16_t data);
	void WriteWord(uint64_t address, uint32_t data);
	void WriteLong(uint64_t address, uint64_t data);

	uint64_t GetSize();

};
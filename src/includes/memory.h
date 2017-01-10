#pragma once
#include <cstdint>
#include <string>
class CMemory {
public:
	std::string name;
	bool littleEndian = true;
	virtual uint8_t  ReadByte  (uint64_t address) = 0;
	virtual uint16_t ReadShort (uint64_t address) = 0;
	virtual uint32_t ReadWord  (uint64_t address) = 0;
	virtual uint64_t ReadLong  (uint64_t address) = 0;

	virtual void WriteByte  (uint64_t address, uint8_t  data) = 0;
	virtual void WriteShort (uint64_t address, uint16_t data) = 0;
	virtual void WriteWord  (uint64_t address, uint32_t data) = 0;
	virtual void WriteLong  (uint64_t address, uint64_t data) = 0;

	virtual uint64_t GetSize() = 0;
	virtual void LoadData(uint8_t * buffer, uint64_t sz) = 0;

};
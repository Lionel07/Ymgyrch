#pragma once
#include <memory.h>
class CMem_RAM : public CMemory {
private:
	uint8_t * memory = NULL;
	uint64_t mem_size = 0;
protected:
	CMem_RAM();
public:
	explicit CMem_RAM(uint64_t size);
	CMem_RAM(uint64_t size, std::string name);
	~CMem_RAM();
	virtual uint8_t  ReadByte(uint64_t address);
	virtual uint16_t ReadShort(uint64_t address);
	virtual uint32_t ReadWord(uint64_t address);
	virtual uint64_t ReadLong(uint64_t address);

	virtual void WriteByte(uint64_t address, uint8_t  data);
	virtual void WriteShort(uint64_t address, uint16_t data);
	virtual void WriteWord(uint64_t address, uint32_t data);
	virtual void WriteLong(uint64_t address, uint64_t data);

	uint64_t GetSize();

};
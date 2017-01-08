#pragma once
#include <vector>
#include <memory.h>
typedef struct mem_mapping
{
	CMemory * dev;
	uint64_t start;
	uint64_t end;
} mem_map_t;

class CMemController {
private:
	

	std::vector<CMemory*> attached_devices;
	std::vector<mem_map_t*> mappings;
	uint64_t address_space;

public:
	CMemController();
	explicit CMemController(uint64_t address_space);
	~CMemController();
	void SetAddressSpace(uint64_t address_space);
	void Map(CMemory * device, uint64_t start);
	void Unmap(CMemory * device);

	virtual mem_map_t * GetDeviceForAddress(uint64_t address);

	uint64_t TranslateAddress(mem_map_t * dev, uint64_t address);

	virtual uint8_t  ReadByte(uint64_t address);
	virtual uint16_t ReadShort(uint64_t address);
	virtual uint32_t ReadWord(uint64_t address);
	virtual uint64_t ReadLong(uint64_t address);

	virtual void WriteByte(uint64_t address, uint8_t  data);
	virtual void WriteShort(uint64_t address, uint16_t data);
	virtual void WriteWord(uint64_t address, uint32_t data);
	virtual void WriteLong(uint64_t address, uint64_t data);

	void DebugPrintMemoryMap();
};
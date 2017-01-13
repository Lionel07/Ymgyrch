#pragma once
#include <memory.h>


/*! Generic RAM */
class Memory_RAM : public Memory {
private:
	uint8_t * memory = NULL;
	uint64_t mem_size = 0;
protected:
	Memory_RAM();
public:
	/// Creates a RAM device of size bytes
	explicit Memory_RAM(uint64_t size);
	/// Creates a RAM device of size bytes, with a name.
	Memory_RAM(uint64_t size, std::string name);
	~Memory_RAM();
	virtual uint8_t  ReadByte(uint64_t address);
	virtual uint16_t ReadShort(uint64_t address);
	virtual uint32_t ReadWord(uint64_t address);
	virtual uint64_t ReadLong(uint64_t address);

	virtual void WriteByte(uint64_t address, uint8_t  data);
	virtual void WriteShort(uint64_t address, uint16_t data);
	virtual void WriteWord(uint64_t address, uint32_t data);
	virtual void WriteLong(uint64_t address, uint64_t data);

	uint64_t GetSize();

	void LoadData(uint8_t * buffer, uint64_t sz);

	/// Load data at an offset. Used for partial patching.
	void LoadData(uint8_t * buffer, uint64_t sz, uint64_t offset);

};
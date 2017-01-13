#pragma once
#include <cstdint>
#include <string>

/*! Generic Memory Device */
class Memory {
public:
	/// The internal name used by this device.
	std::string name;
	/// Is the device Little Endian? Affects byte order.
	bool littleEndian = true;

	/// Read from address
	virtual uint8_t  ReadByte  (uint64_t address) = 0;
	/// Read from address
	virtual uint16_t ReadShort (uint64_t address) = 0;
	/// Read from address
	virtual uint32_t ReadWord  (uint64_t address) = 0;
	/// Read from address
	virtual uint64_t ReadLong  (uint64_t address) = 0;

	/// Write data to address
	virtual void WriteByte  (uint64_t address, uint8_t  data) = 0;
	/// Write data to address
	virtual void WriteShort (uint64_t address, uint16_t data) = 0;
	/// Write data to address
	virtual void WriteWord  (uint64_t address, uint32_t data) = 0;
	/// Write data to address
	virtual void WriteLong  (uint64_t address, uint64_t data) = 0;

	/// How big is this device?
	virtual uint64_t GetSize() = 0;
	/// Populate the memory with data.
	virtual void LoadData(uint8_t * buffer, uint64_t sz) = 0;

};
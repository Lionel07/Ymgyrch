#pragma once
#include <vector>
#include <memory.h>

/// A memory mapping for the memory controller
typedef struct mem_map {
	/// The device that is mappped
	Memory * dev;
	/// Where its domain starts
	uint64_t start;
	/// Where its domain ends
	uint64_t end;
} mem_map_t;

/*! A memory controller.
*   Manages multiple devices in one memory space.
*/
class MemoryController {
public:
	
	/// Creates an empty memory controller
	MemoryController();
	/// Creates an empty memory controller of size address_space
	explicit MemoryController(uint64_t address_space);
	~MemoryController();
	/// Sets the address space that can be accessed
	void SetAddressSpace(uint64_t address_space);
	/// Maps device to start, to start + size
	void Map(Memory * device, uint64_t start);
	/// Unmaps device from the address space.
	void Unmap(Memory * device);

	/// Get the memory mapping for a particular address.
	virtual mem_map_t * GetDeviceForAddress(uint64_t address);

	/// Translates an address into device local addressing (array bounds)
	uint64_t TranslateAddress(mem_map_t * dev, uint64_t address);


	/// Reads from the device pointed to by address
	virtual uint8_t  ReadByte(uint64_t address);
	/// Reads from the device pointed to by address
	virtual uint16_t ReadShort(uint64_t address);
	/// Reads from the device pointed to by address
	virtual uint32_t ReadWord(uint64_t address);
	/// Reads from the device pointed to by address
	virtual uint64_t ReadLong(uint64_t address);

	/// Writes data to the device pointed to by address
	virtual void WriteByte(uint64_t address, uint8_t  data);
	/// Writes data to the device pointed to by address
	virtual void WriteShort(uint64_t address, uint16_t data);
	/// Writes data to the device pointed to by address
	virtual void WriteWord(uint64_t address, uint32_t data);
	/// Writes data to the device pointed to by address
	virtual void WriteLong(uint64_t address, uint64_t data);

	/// Print the memory map to the log, for testing.
	void DebugPrintMemoryMap();
private:

	/// Every device attached on this bus
	std::vector<Memory*> attached_devices;
	std::vector<mem_map_t*> mappings;
	uint64_t address_space;
};
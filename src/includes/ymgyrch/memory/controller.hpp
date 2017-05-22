#pragma once
#include <vector>
#include <cstdint>
#include <ymgyrch/memory/device.hpp>

namespace Ymgyrch {
namespace Memory {

typedef struct memory_mapping {
    Device * dev;
    uint64_t start;
    uint64_t end;
} memory_mapping_t;

class Controller {
private:
    std::vector<Device*> devices;
	std::vector<memory_mapping_t*> mappings;
	uint64_t address_space = 0;
public:
	Controller();
	Controller(uint64_t address);
	memory_mapping_t * GetMapping(uint64_t address);
    /// Translates an address into device local addressing (array bounds)
    uint64_t TranslateAddress(memory_mapping_t * dev, uint64_t address);

    /// Sets the address space that can be accessed
    void SetAddressSpace(uint64_t address_space);

    /// Maps device to start, to start + size
    void Map(Device * device, uint64_t start);
    /// Unmaps device from the address space.
    void Unmap(Device * device);

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
};
};
};

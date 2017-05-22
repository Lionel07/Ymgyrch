#pragma once
#include <ymgyrch/memory/device.hpp>
#include <cstdint>
namespace Ymgyrch {
namespace Memory {
class RAM : public Device {
private:
	uint8_t * buffer;
	uint64_t size;
public:
    RAM(uint64_t sz);
    /// Read from address
    virtual uint8_t  ReadByte  (uint64_t address);
    /// Read from address
    virtual uint16_t ReadShort (uint64_t address);
    /// Read from address
    virtual uint32_t ReadWord  (uint64_t address);
    /// Read from address
    virtual uint64_t ReadLong  (uint64_t address);

    /// Write data to address
    virtual void WriteByte  (uint64_t address, uint8_t  data);
    /// Write data to address
    virtual void WriteShort (uint64_t address, uint16_t data);
    /// Write data to address
    virtual void WriteWord  (uint64_t address, uint32_t data);
    /// Write data to address
    virtual void WriteLong  (uint64_t address, uint64_t data);

    /// How big is this device?
    virtual uint64_t GetSize();
    /// Populate the memory with data.
    virtual void LoadData(uint8_t * buffer, uint64_t sz);
};
};
};

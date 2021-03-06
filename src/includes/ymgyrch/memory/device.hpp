#pragma once
#include <cstdint>
#include <string>

namespace Ymgyrch {
namespace Memory {
class Device {
public:
    std::string name;
    bool littleEndian = true;
	Device() {};
	Device(uint64_t sz) {};

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
};
};

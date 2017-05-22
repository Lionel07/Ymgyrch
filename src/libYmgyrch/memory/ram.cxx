#include <ymgyrch/memory/ram.hpp>

Ymgyrch::Memory::RAM::RAM(uint64_t sz)
{
	size = sz;
	buffer = new uint8_t[sz];
}

uint8_t Ymgyrch::Memory::RAM::ReadByte(uint64_t address)
{
	if (address > size) { return 0; }
	return buffer[address];
}

uint16_t Ymgyrch::Memory::RAM::ReadShort(uint64_t address)
{
    uint8_t a;
	uint8_t b;

	a = ReadByte(address + 1);
	b = ReadByte(address + 0);

	uint16_t ret = (uint16_t)((a << 8) | (b & 0xff));
	return ret;
}

uint32_t Ymgyrch::Memory::RAM::ReadWord(uint64_t address)
{
    uint16_t a = ReadShort(address);
    uint16_t b = ReadShort(address + 2);
    return (uint32_t)((a << 16) | (b & 0xffff));
}

uint64_t Ymgyrch::Memory::RAM::ReadLong(uint64_t address)
{
    uint32_t a = ReadWord(address);
    uint32_t b = ReadWord(address + 2);
    return (uint64_t)((a << 16) | (b & 0xffffffff));
}

void Ymgyrch::Memory::RAM::WriteByte(uint64_t address, uint8_t data)
{
    if (address > size) { return; }
    buffer[address] = data;
}

void Ymgyrch::Memory::RAM::WriteShort(uint64_t address, uint16_t data)
{
    WriteByte(address, (unsigned char)((data & 0xff00) >> 8));
	WriteByte(address + 1, (unsigned char)(data & 0x00ff));
}

void Ymgyrch::Memory::RAM::WriteWord(uint64_t address, uint32_t data)
{
    WriteShort(address, (unsigned char)(data & 0x0000ffff));
    WriteShort(address + 2, (unsigned char)((data & 0xffff0000) >> 16));
}

void Ymgyrch::Memory::RAM::WriteLong(uint64_t address, uint64_t data)
{
    if (address > size) { return; }
}

uint64_t Ymgyrch::Memory::RAM::GetSize()
{
	return size;
}

void Ymgyrch::Memory::RAM::LoadData(uint8_t * buf, uint64_t sz)
{
    uint64_t maxsz = size;
	if (sz < maxsz) {
		maxsz = sz;
	}

	memcpy(this->buffer, buf, maxsz);
}

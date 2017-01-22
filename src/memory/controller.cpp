#include <algorithm>
#include <memcontroller.h>
#include <log.h>
MemoryController::MemoryController()
{
}

MemoryController::MemoryController(uint64_t address_space)
{
	SetAddressSpace(address_space);
}

MemoryController::~MemoryController()
{
	// Delete every device in attached_devices
	// Delete every mapping in mappings
}

void MemoryController::SetAddressSpace(uint64_t address_space)
{
	this->address_space = address_space;
}

void MemoryController::Map(Memory * device, uint64_t start)
{
	mem_map_t * mapping = new mem_map_t;
	mapping->dev = device;
	mapping->start = start;
	mapping->end = device->GetSize() + start - 1;
	attached_devices.push_back(device);

	mappings.push_back(mapping);

	std::sort(mappings.begin(), mappings.end(), compareMappings);
}

void MemoryController::Unmap(Memory * device)
{
	/// @todo Implement this
}

mem_map_t * MemoryController::GetDeviceForAddress(uint64_t address) {
	for each (mem_map_t * dev in mappings)
	{
		if (address >= dev->start && address <= dev->end)
		{
			return dev;
		}
	}

	return nullptr;
}

uint64_t MemoryController::TranslateAddress(mem_map_t * dev, uint64_t address) {
	return address - dev->start;
}

uint8_t MemoryController::ReadByte(uint64_t address)
{
	mem_map_t * dev = GetDeviceForAddress(address);
	if (dev != nullptr)
	{
		//g_log->Log("MEM", "Read to %s, address 0x%04X, real 0x%04X",dev->dev->name.c_str(), address, TranslateAddress(dev, address));
		return dev->dev->ReadByte(TranslateAddress(dev, address));
	}
	else
	{
		g_log->Warn("MEM", "Read to unmapped memory (0x{0:X})", address);
		return 0;
	}
}

uint16_t MemoryController::ReadShort(uint64_t address)
{
	mem_map_t * dev = GetDeviceForAddress(address);
	if (dev != nullptr)
	{
		return dev->dev->ReadShort(TranslateAddress(dev, address));
	}
	else
	{
		g_log->Warn("MEM", "Read to unmapped memory (0x{0:X})", address);
		return 0;
	}
}

uint32_t MemoryController::ReadWord(uint64_t address)
{
	mem_map_t * dev = GetDeviceForAddress(address);
	if (dev != nullptr)
	{
		return dev->dev->ReadWord(TranslateAddress(dev, address));
	}
	else
	{
		g_log->Warn("MEM", "Read to unmapped memory (0x{0:X})", address);
		return 0;
	}
}

uint64_t MemoryController::ReadLong(uint64_t address)
{
	mem_map_t * dev = GetDeviceForAddress(address);
	if (dev != nullptr)
	{
		return dev->dev->ReadLong(TranslateAddress(dev, address));
	}
	else
	{
		g_log->Warn("MEM", "Read to unmapped memory (0x{0:X})", address);
		return 0;
	}
}

void MemoryController::WriteByte(uint64_t address, uint8_t data)
{
	mem_map_t * dev = GetDeviceForAddress(address);
	if (dev != nullptr)
	{
		dev->dev->WriteByte(TranslateAddress(dev, address), data);
	}
}

void MemoryController::WriteShort(uint64_t address, uint16_t data)
{
	mem_map_t * dev = GetDeviceForAddress(address);
	if (dev != nullptr)
	{
		dev->dev->WriteShort(TranslateAddress(dev, address), data);
	}
}

void MemoryController::WriteWord(uint64_t address, uint32_t data)
{
	mem_map_t * dev = GetDeviceForAddress(address);
	if (dev != nullptr)
	{
		dev->dev->WriteWord(TranslateAddress(dev, address), data);
	}
}

void MemoryController::WriteLong(uint64_t address, uint64_t data)
{
	mem_map_t * dev = GetDeviceForAddress(address);
	if (dev != nullptr)
	{
		dev->dev->WriteLong(TranslateAddress(dev, address), data);
	}
}

void MemoryController::DebugPrintMemoryMap()
{
	g_log->Log("MEM", "Memory Map:");

	std::vector<mem_map_t*> mappings_sorted;

	for (uint64_t j = 0; j <= address_space; j += 0x0001)
	{
		for (uint64_t i = 0; i < mappings.size(); i += 1)
		{
			if (mappings[i]->start == j)
			{
				mappings_sorted.push_back(mappings[i]);
				continue;
			}
		}
	}

	for (size_t i = 0; i < mappings_sorted.size(); i += 1)
	{
		g_log->Log("MEM", "{0:9s} : 0x{1:04X} => 0x{2:04X}", mappings_sorted[i]->dev->name.c_str(), mappings_sorted[i]->start, mappings_sorted[i]->end);
	}
}

bool MemoryController::compareMappings(mem_map_t * a, mem_map_t * b)
{
	return a->start < b->start;
}
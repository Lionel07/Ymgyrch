#include <ymgyrch/memory/controller.hpp>
#include <ymgyrch/memory/device.hpp>

Ymgyrch::Memory::Controller::Controller() {
}

Ymgyrch::Memory::Controller::Controller(uint64_t address) {

	SetAddressSpace(address);
}

Ymgyrch::Memory::memory_mapping_t * Ymgyrch::Memory::Controller::GetMapping(uint64_t address) {
	memory_mapping_t * final = nullptr;
	for each (memory_mapping_t* mapping in mappings) {
		if (address >= mapping->start && address < mapping->end) {
			final = mapping;
			break;
		}
	}
	return final;
}

uint64_t Ymgyrch::Memory::Controller::TranslateAddress(memory_mapping_t * dev, uint64_t address) {
	return address - dev->start;
}

void Ymgyrch::Memory::Controller::SetAddressSpace(uint64_t address_space) {
	this->address_space = address_space;
}

void Ymgyrch::Memory::Controller::Map(Device * device, uint64_t start) {
	memory_mapping_t * mapping = new memory_mapping_t();
	mapping->dev = device;
	mapping->start = start;
	mapping->end = start + device->GetSize();
	mappings.push_back(mapping);
}

void Ymgyrch::Memory::Controller::Unmap(Device * device) {
	for each (memory_mapping_t* mapping in mappings) {
		if (mapping->dev == device) {
			std::vector<memory_mapping_t*>::iterator position = std::find(mappings.begin(), mappings.end(), mapping);
			if (position != mappings.end()) // == myVector.end() means the element was not found
				mappings.erase(position);
			return;
		}
	}
}

uint8_t Ymgyrch::Memory::Controller::ReadByte(uint64_t address) {
	memory_mapping_t * dev = GetMapping(address);
	if (dev == nullptr) { return 0; }
	return dev->dev->ReadByte(TranslateAddress(dev, address));
}

uint16_t Ymgyrch::Memory::Controller::ReadShort(uint64_t address) {
	memory_mapping_t * dev = GetMapping(address);
	if (dev == nullptr) { return 0; }
	return dev->dev->ReadShort(TranslateAddress(dev, address));
}

uint32_t Ymgyrch::Memory::Controller::ReadWord(uint64_t address) {
	memory_mapping_t * dev = GetMapping(address);
	if (dev == nullptr) { return 0; }
	return dev->dev->ReadWord(TranslateAddress(dev, address));
}

uint64_t Ymgyrch::Memory::Controller::ReadLong(uint64_t address) {
	memory_mapping_t * dev = GetMapping(address);
	if (dev == nullptr) { return 0; }
	return dev->dev->ReadLong(TranslateAddress(dev, address));
}

void Ymgyrch::Memory::Controller::WriteByte(uint64_t address, uint8_t data) {
	memory_mapping_t * dev = GetMapping(address);
	if (dev == nullptr) { return; }
	dev->dev->WriteByte(TranslateAddress(dev, address), data);
}

void Ymgyrch::Memory::Controller::WriteShort(uint64_t address, uint16_t data) {
	memory_mapping_t * dev = GetMapping(address);
	if (dev == nullptr) { return; }
	dev->dev->WriteShort(TranslateAddress(dev, address), data);
}

void Ymgyrch::Memory::Controller::WriteWord(uint64_t address, uint32_t data) {
	memory_mapping_t * dev = GetMapping(address);
	if (dev == nullptr) { return; }
	dev->dev->WriteWord(TranslateAddress(dev, address), data);
}

void Ymgyrch::Memory::Controller::WriteLong(uint64_t address, uint64_t data) {
	memory_mapping_t * dev = GetMapping(address);
	if (dev == nullptr) { return; }
	dev->dev->WriteLong(TranslateAddress(dev, address), data);
}

#include "Bus.h"

void Bus::attach_cpu(CPU& cpu)
{
	this->cpu = &cpu;
	cpu.bus = this;
}

void Bus::insert_cartridge(Cartridge& cartridge)
{
	this->cartridge = &cartridge;
}

uint8_t Bus::read(uint16_t address)
{
	if (address < 0x4000) {
		return cartridge->ROM[address];
	}
	
	// todo: set up reading from other readable spaces in memory.

	return 0;
}

void Bus::write(uint16_t address, uint8_t data)
{
	// todo: set up writing to writable spaces in memory.
}

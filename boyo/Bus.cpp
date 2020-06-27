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
	return 0;
}

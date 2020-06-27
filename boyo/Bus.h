#ifndef BUS_H
#define BUS_H

#include <stdint.h>
#include "CPU.h"
#include "Cartridge.h"

class CPU;

class Bus
{
public:
	CPU* cpu;
	Cartridge* cartridge;
	uint8_t RAM[8192];
	uint8_t VRAM[8192];

	void attach_cpu(CPU& cpu);
	void insert_cartridge(Cartridge& cartridge);
	uint8_t read(uint16_t address);
};

#endif

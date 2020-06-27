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
	uint8_t RAM[0x2000];
	uint8_t VRAM[0x2000];

	void attach_cpu(CPU& cpu);
	void insert_cartridge(Cartridge& cartridge);
	uint8_t read(uint16_t address);
	void write(uint16_t address, uint8_t data);
};

#endif

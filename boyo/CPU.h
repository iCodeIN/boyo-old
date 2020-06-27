#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "Bus.h"

class Bus;

class CPU
{
public:
	Bus* bus;
	uint16_t sp;
	uint16_t pc;
	uint8_t registers[8];

	CPU();
	void execute(int cycles);

private:
	int (CPU::* opcode_table[16][16])();

	int execute();
	void increment_pc(int bytes);
	int NOP();
	int LD_imm8(int reg);
	int LD_06();
	int LD_0E();
	int LD_16();
	int LD_1E();
	int LD_26();
	int LD_2E();
};

#endif

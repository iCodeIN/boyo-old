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
	int LD_imm8(int reg);
	void LD_reg(int reg1, int reg2);
	int NOP();
	int LD_06();
	int LD_0E();
	int LD_16();
	int LD_1E();
	int LD_26();
	int LD_2E();
	int LD_78();
	int LD_79();
	int LD_7A();
	int LD_7B();
	int LD_7C();
	int LD_7D();
	int LD_7F();
};

#endif

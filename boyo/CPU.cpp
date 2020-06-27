#include "CPU.h"

CPU::CPU()
{
	pc = 0x100;
	sp = 0xFFFE;
	opcode_table[0x0][0x6] = &CPU::LD_06;
	opcode_table[0x0][0xE] = &CPU::LD_0E;
	opcode_table[0x1][0x6] = &CPU::LD_16;
	opcode_table[0x1][0xE] = &CPU::LD_1E;
	opcode_table[0x2][0x6] = &CPU::LD_26;
	opcode_table[0x2][0xE] = &CPU::LD_2E;
}

void CPU::execute(int cycles)
{
	int completed = 0;
	while (completed < cycles)
		completed += execute();
}

int CPU::execute()
{
	uint8_t opcode = bus->read(pc);
	return (this->*opcode_table[opcode >> 4][opcode & 0xF])();
}

int CPU::LD_imm8(int reg)
{
	registers[reg] = bus->read(pc + 8);
	pc += 16;
	return 8;
}

int CPU::LD_06()
{
	return LD_imm8(1);
}

int CPU::LD_0E()
{
	return LD_imm8(2);
}

int CPU::LD_16()
{
	return LD_imm8(3);
}

int CPU::LD_1E()
{
	return LD_imm8(4);
}

int CPU::LD_26()
{
	return LD_imm8(6);
}

int CPU::LD_2E()
{
	return LD_imm8(7);
}

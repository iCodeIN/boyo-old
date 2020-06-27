#include "CPU.h"

CPU::CPU()
{
	pc = 0x100;
	sp = 0xFFFE;
	opcode_table[0x0][0x0] = &CPU::NOP;
	opcode_table[0x0][0x6] = &CPU::LD_06;
	opcode_table[0x0][0xE] = &CPU::LD_0E;
	opcode_table[0x1][0x6] = &CPU::LD_16;
	opcode_table[0x1][0xE] = &CPU::LD_1E;
	opcode_table[0x2][0x6] = &CPU::LD_26;
	opcode_table[0x2][0xE] = &CPU::LD_2E;
}

// Executes instructions until the given number of cycles have occurred.
void CPU::execute(int cycles)
{
	int completed = 0;
	while (completed < cycles)
		completed += execute();
}

// Executes a single instruction and returns the number of cycles that it took.
int CPU::execute()
{
	uint8_t opcode = bus->read(pc);
	return (this->*opcode_table[opcode >> 4][opcode & 0xF])();
}

// Increments the PC by a given number of bytes.
void CPU::increment_pc(int bytes = 1)
{
	pc += bytes;
}

// Reads the byte after the current instruction into the given register.
int CPU::LD_imm8(int r)
{
	registers[r] = bus->read(pc + 8);
	increment_pc(2);
	return 8;
}

// Puts the value of r2 into r1.
void CPU::LD_reg(int r1, int r2)
{
	registers[r1] = registers[r2];
}

int CPU::NOP()
{
	increment_pc();
	return 4;
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

int CPU::LD_78()
{
	LD_reg(0, 1);
	return 4;
}

int CPU::LD_79()
{
	LD_reg(0, 2);
	return 4;
}

int CPU::LD_7A()
{
	LD_reg(0, 3);
	return 4;
}

int CPU::LD_7B()
{
	LD_reg(0, 4);
	return 4;
}

int CPU::LD_7C()
{
	LD_reg(0, 6);
	return 4;
}

int CPU::LD_7D()
{
	LD_reg(0, 7);
	return 4;
}

int CPU::LD_7F()
{
	LD_reg(0, 0);
	return 4;
}
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
	opcode_table[0x3][0x6] = &CPU::LD_36;
	opcode_table[0x4][0x0] = &CPU::LD_40;
	opcode_table[0x4][0x1] = &CPU::LD_41;
	opcode_table[0x4][0x2] = &CPU::LD_42;
	opcode_table[0x4][0x3] = &CPU::LD_43;
	opcode_table[0x4][0x4] = &CPU::LD_44;
	opcode_table[0x4][0x5] = &CPU::LD_45;
	opcode_table[0x4][0x6] = &CPU::LD_46;
	opcode_table[0x4][0x8] = &CPU::LD_48;
	opcode_table[0x4][0x9] = &CPU::LD_49;
	opcode_table[0x4][0xA] = &CPU::LD_4A;
	opcode_table[0x4][0xB] = &CPU::LD_4B;
	opcode_table[0x4][0xC] = &CPU::LD_4C;
	opcode_table[0x4][0xD] = &CPU::LD_4D;
	opcode_table[0x4][0xE] = &CPU::LD_4E;
	opcode_table[0x5][0x0] = &CPU::LD_50;
	opcode_table[0x5][0x1] = &CPU::LD_51;
	opcode_table[0x5][0x2] = &CPU::LD_52;
	opcode_table[0x5][0x3] = &CPU::LD_53;
	opcode_table[0x5][0x4] = &CPU::LD_54;
	opcode_table[0x5][0x5] = &CPU::LD_55;
	opcode_table[0x5][0x6] = &CPU::LD_56;
	opcode_table[0x5][0x8] = &CPU::LD_58;
	opcode_table[0x5][0x9] = &CPU::LD_59;
	opcode_table[0x5][0xA] = &CPU::LD_5A;
	opcode_table[0x5][0xB] = &CPU::LD_5B;
	opcode_table[0x5][0xC] = &CPU::LD_5C;
	opcode_table[0x5][0xD] = &CPU::LD_5D;
	opcode_table[0x5][0xE] = &CPU::LD_5E;
	opcode_table[0x6][0x0] = &CPU::LD_60;
	opcode_table[0x6][0x1] = &CPU::LD_61;
	opcode_table[0x6][0x2] = &CPU::LD_62;
	opcode_table[0x6][0x3] = &CPU::LD_63;
	opcode_table[0x6][0x4] = &CPU::LD_64;
	opcode_table[0x6][0x5] = &CPU::LD_65;
	opcode_table[0x6][0x6] = &CPU::LD_66;
	opcode_table[0x6][0x8] = &CPU::LD_68;
	opcode_table[0x6][0x9] = &CPU::LD_69;
	opcode_table[0x6][0xA] = &CPU::LD_6A;
	opcode_table[0x6][0xB] = &CPU::LD_6B;
	opcode_table[0x6][0xC] = &CPU::LD_6C;
	opcode_table[0x6][0xD] = &CPU::LD_6D;
	opcode_table[0x6][0xE] = &CPU::LD_6E;
	opcode_table[0x7][0x0] = &CPU::LD_70;
	opcode_table[0x7][0x1] = &CPU::LD_71;
	opcode_table[0x7][0x2] = &CPU::LD_72;
	opcode_table[0x7][0x3] = &CPU::LD_73;
	opcode_table[0x7][0x4] = &CPU::LD_74;
	opcode_table[0x7][0x5] = &CPU::LD_75;
	opcode_table[0x7][0x8] = &CPU::LD_78;
	opcode_table[0x7][0x9] = &CPU::LD_79;
	opcode_table[0x7][0xA] = &CPU::LD_7A;
	opcode_table[0x7][0xB] = &CPU::LD_7B;
	opcode_table[0x7][0xC] = &CPU::LD_7C;
	opcode_table[0x7][0xD] = &CPU::LD_7D;
	opcode_table[0x7][0xE] = &CPU::LD_7E;
	opcode_table[0x7][0xF] = &CPU::LD_7F;
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
	registers[r] = bus->read(pc + 1);
	increment_pc(2);
	return 8;
}

// Puts the value of r2 into r1.
int CPU::LD_reg(int r1, int r2)
{
	registers[r1] = registers[r2];
	increment_pc();
	return 4;
}

// Reads the value from the given address into the specified register.
int CPU::LD_from_address(int r, uint16_t address)
{
	registers[r] = bus->read(address);
	increment_pc();
	return 8;
}

// Writes the value from the given register to the specified address.
int CPU::LD_to_address(int r, uint16_t address)
{
	bus->write(address, registers[r]);
	increment_pc();
	return 8;
}

int CPU::HL()
{
	return (registers[6] << 8) | registers[7];
}

int CPU::NOP()
{
	increment_pc();
	return 4;
}

// LD B, n
int CPU::LD_06()
{
	return LD_imm8(1);
}

// LD C, n
int CPU::LD_0E()
{
	return LD_imm8(2);
}

// LD D, n
int CPU::LD_16()
{
	return LD_imm8(3);
}

// LD E, n
int CPU::LD_1E()
{
	return LD_imm8(4);
}

// LD H, n
int CPU::LD_26()
{
	return LD_imm8(6);
}

// LD L, n
int CPU::LD_2E()
{
	return LD_imm8(7);
}

// LD (HL), n
int CPU::LD_36()
{
	bus->write(HL(), bus->read(pc + 1));
	increment_pc(2);
	return 12;
}

// LD B, B
int CPU::LD_40()
{
	return LD_reg(1, 1);
}

// LD B, C
int CPU::LD_41()
{
	return LD_reg(1, 2);
}

// LD B, D
int CPU::LD_42()
{
	return LD_reg(1, 3);
}

// LD B, E
int CPU::LD_43()
{
	return LD_reg(1, 4);
}

// LD B, H
int CPU::LD_44()
{
	return LD_reg(1, 6);
}

// LD B, L
int CPU::LD_45()
{
	return LD_reg(1, 7);
}

// LD B, (HL)
int CPU::LD_46()
{
	return LD_from_address(1, HL());
}

// LD C, B
int CPU::LD_48()
{
	return LD_reg(2, 1);
}

// LD C, C
int CPU::LD_49()
{
	return LD_reg(2, 2);
}

// LD C, D
int CPU::LD_4A()
{
	return LD_reg(2, 3);
}

// LD C, E
int CPU::LD_4B()
{
	return LD_reg(2, 4);
}

// LD C, H
int CPU::LD_4C()
{
	return LD_reg(2, 6);
}

// LD C, L
int CPU::LD_4D()
{
	return LD_reg(2, 7);
}

// LD C, (HL)
int CPU::LD_4E()
{
	return LD_from_address(2, HL());
}

// LD D, B
int CPU::LD_50()
{
	return LD_reg(3, 1);
}

// LD D, C
int CPU::LD_51()
{
	return LD_reg(3, 2);
}

// LD D, D
int CPU::LD_52()
{
	return LD_reg(3, 3);
}

// LD D, E
int CPU::LD_53()
{
	return LD_reg(3, 4);
}

// LD D, H
int CPU::LD_54()
{
	return LD_reg(3, 6);
}

// LD D, L
int CPU::LD_55()
{
	return LD_reg(3, 7);
}

// LD D, (HL)
int CPU::LD_56()
{
	return LD_from_address(3, HL());
}

// LD E, B
int CPU::LD_58()
{
	return LD_reg(4, 1);
}

// LD E, C
int CPU::LD_59()
{
	return LD_reg(4, 2);
}

// LD E, D
int CPU::LD_5A()
{
	return LD_reg(4, 3);
}

// LD E, E
int CPU::LD_5B()
{
	return LD_reg(4, 4);
}

// LD E, H
int CPU::LD_5C()
{
	return LD_reg(4, 6);
}

// LD E, L
int CPU::LD_5D()
{
	return LD_reg(4, 7);
}

// LD E, (HL)
int CPU::LD_5E()
{
	return LD_from_address(4, HL());
}

// LD H, B
int CPU::LD_60()
{
	return LD_reg(6, 1);
}

// LD H, C
int CPU::LD_61()
{
	return LD_reg(6, 2);
}

// LD H, D
int CPU::LD_62()
{
	return LD_reg(6, 3);
}

// LD H, E
int CPU::LD_63()
{
	return LD_reg(6, 4);
}

// LD H, H
int CPU::LD_64()
{
	return LD_reg(6, 6);
}

// LD H, L
int CPU::LD_65()
{
	return LD_reg(6, 7);
}

// LD H, (HL)
int CPU::LD_66()
{
	return LD_from_address(6, HL());
}

// LD L, B
int CPU::LD_68()
{
	return LD_reg(7, 1);
}

// LD L, C
int CPU::LD_69()
{
	return LD_reg(7, 2);
}

// LD L, D
int CPU::LD_6A()
{
	return LD_reg(7, 3);
}

// LD L, E
int CPU::LD_6B()
{
	return LD_reg(7, 4);
}

// LD L, H
int CPU::LD_6C()
{
	return LD_reg(7, 6);
}

// LD L, L
int CPU::LD_6D()
{
	return LD_reg(7, 7);
}

// LD L, (HL)
int CPU::LD_6E()
{
	return LD_from_address(7, HL());
}

// LD (HL), B
int CPU::LD_70()
{
	return LD_to_address(1, HL());
}

// LD (HL), C
int CPU::LD_71()
{
	return LD_to_address(2, HL());
}

// LD (HL), D
int CPU::LD_72()
{
	return LD_to_address(3, HL());
}

// LD (HL), E
int CPU::LD_73()
{
	return LD_to_address(4, HL());
}

// LD (HL), H
int CPU::LD_74()
{
	return LD_to_address(6, HL());
}

// LD (HL), L
int CPU::LD_75()
{
	return LD_to_address(7, HL());
}

// LD A, B
int CPU::LD_78()
{
	return LD_reg(0, 1);
}

// LD A, C
int CPU::LD_79()
{
	return LD_reg(0, 2);
}

// LD A, D
int CPU::LD_7A()
{
	return LD_reg(0, 3);
}

// LD A, E
int CPU::LD_7B()
{
	return LD_reg(0, 4);
}

// LD A, H
int CPU::LD_7C()
{
	return LD_reg(0, 6);
}

// LD A, L
int CPU::LD_7D()
{
	return LD_reg(0, 7);
}

// LD A, (HL)
int CPU::LD_7E()
{
	return LD_from_address(0, HL());
}

// LD A, A
int CPU::LD_7F()
{
	return LD_reg(0, 0);
}

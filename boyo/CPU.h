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
	int HL();

private:
	int (CPU::* opcode_table[16][16])();

	int execute();
	void increment_pc(int bytes);

	int LD_imm8(int reg);
	int LD_reg(int reg1, int reg2);
	int LD_from_address(int r, uint16_t address);
	int LD_to_address(int r, uint16_t address);

	int NOP();
	int LD_06();
	int LD_0E();
	int LD_16();
	int LD_1E();
	int LD_26();
	int LD_2E();
	int LD_36();
	int LD_40();
	int LD_41();
	int LD_42();
	int LD_43();
	int LD_44();
	int LD_45();
	int LD_46();
	int LD_48();
	int LD_49();
	int LD_4A();
	int LD_4B();
	int LD_4C();
	int LD_4D();
	int LD_4E();
	int LD_50();
	int LD_51();
	int LD_52();
	int LD_53();
	int LD_54();
	int LD_55();
	int LD_56();
	int LD_58();
	int LD_59();
	int LD_5A();
	int LD_5B();
	int LD_5C();
	int LD_5D();
	int LD_5E();
	int LD_60();
	int LD_61();
	int LD_62();
	int LD_63();
	int LD_64();
	int LD_65();
	int LD_66();
	int LD_68();
	int LD_69();
	int LD_6A();
	int LD_6B();
	int LD_6C();
	int LD_6D();
	int LD_6E();
	int LD_70();
	int LD_71();
	int LD_72();
	int LD_73();
	int LD_74();
	int LD_75();
	int LD_78();
	int LD_79();
	int LD_7A();
	int LD_7B();
	int LD_7C();
	int LD_7D();
	int LD_7E();
	int LD_7F();
};

#endif

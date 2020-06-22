#ifndef CPU_H
#define CPU_H

#include "Bus.h"

class Bus;

class CPU
{
public:
	Bus* bus;
	void execute(int cycles);
};

#endif

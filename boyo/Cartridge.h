#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <stdint.h>

class Cartridge
{
public:
	uint8_t ROM[16384];
	static int load_file(Cartridge* cartridge, const char* filename);
};

#endif

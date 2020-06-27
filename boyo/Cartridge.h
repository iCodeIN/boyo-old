#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <stdint.h>
#include <string>

class Cartridge
{
public:
	uint8_t ROM[0x4000];
	static int load_file(Cartridge& cartridge, const std::string& filename);
};

#endif

#include <iostream>
#include <string>
#include "Bus.h"
#include "CPU.h"

#define CYCLES_PER_FRAME 100

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: boyo <ROM file>" << std::endl;
        return 1;
    }

    std::string filename(argv[1]);

    Bus bus;
    CPU cpu;
    bus.attach_cpu(cpu);

    Cartridge cartridge;
    Cartridge::load_file(cartridge, filename);
    bus.insert_cartridge(cartridge);

    while (true) {
        cpu.execute(CYCLES_PER_FRAME);
    }

    return 0;
}

#include <algorithm>
#include <fstream>
#include "Cartridge.h"

int Cartridge::load_file(Cartridge& cartridge, const std::string& filename)
{
    std::fstream file;
    file.open(filename, std::ios::in | std::ios::binary | std::ios::ate);

    if (!file.good())
        return 1;

    int size = std::min(static_cast<int>(file.tellg()), 0x4000);
    auto data = new unsigned char[size];
    file.seekg(std::ios::beg);
    file.read((char*)(&data[0]), size);
    file.close();

    // todo: look into a way to do this without having to load the file into a temporary buffer.
    for (int i = 0; i < size; i++)
        cartridge.ROM[i] = static_cast<uint8_t>(data[i]);

    delete[] data;
    return 0;
}

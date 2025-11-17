#include "DXFReader.h"
#include <iostream>
#include <fstream>
#include <string>

DXFReader::DXFReader(const std::string& filename) : m_filename(filename) {}

bool DXFReader::read() {
    std::ifstream file(m_filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open DXF file: " << m_filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Process each line of the DXF file
        // This is a placeholder for actual DXF parsing logic
        std::cout << line << std::endl;
    }

    file.close();
    return true;
}
#include "DXFWriter.h"
#include <fstream>
#include <iostream>

DXFWriter::DXFWriter(const std::string& filename) : m_filename(filename) {}

void DXFWriter::writeHeader() {
    m_file << "0\nSECTION\n2\nHEADER\n0\nENDSEC\n";
}

void DXFWriter::writeEntities(const std::vector<Entity>& entities) {
    for (const auto& entity : entities) {
        m_file << "0\n" << entity.type << "\n";
        m_file << "10\n" << entity.x << "\n";
        m_file << "20\n" << entity.y << "\n";
        m_file << "30\n" << entity.z << "\n";
    }
}

void DXFWriter::writeFooter() {
    m_file << "0\nEOF\n";
}

bool DXFWriter::save(const std::vector<Entity>& entities) {
    m_file.open(m_filename);
    if (!m_file.is_open()) {
        std::cerr << "Error opening file: " << m_filename << std::endl;
        return false;
    }

    writeHeader();
    writeEntities(entities);
    writeFooter();

    m_file.close();
    return true;
}
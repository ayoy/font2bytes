#include "sourcecodegenerator.h"

SourceCodeGenerator::SourceCodeGenerator(const SourceCodeOptions &options):
    options(options),
    m_stream(new std::ostringstream)
{
}

SourceCodeGenerator::~SourceCodeGenerator()
{
    if (m_stream) {
        delete m_stream;
        m_stream = nullptr;
    }
}

CCodeGenerator::CCodeGenerator(const SourceCodeOptions &options) :
    SourceCodeGenerator(options)
{
}

void CCodeGenerator::begin()
{
    stream().flush();
    stream() << "//\n// Font Data\n// Created: \(dateTime)\n//\n";
}

void CCodeGenerator::beginArray(const std::string &name)
{
    stream() << "\n\nconst unsigned char " << name << "[] = {\n\t";
}

void CCodeGenerator::writeByte(uint8_t byte)
{
    if (options.bitNumbering == SourceCodeOptions::BitNumbering::MSB) {
        uint8_t reversedByte = 0;
        for (uint8_t i = 0; i < 8; i++) {
            if ((byte & (1<<i)) != 0) {
                uint8_t setBit = 1<<(7-i);
                reversedByte |= setBit;
            }
        }
        byte = reversedByte;
    }
    if (options.shouldInvertBits) {
        byte = ~byte;
    }

    auto format = "0x%02X,";
    std::string byteString(5, '\0');
    std::sprintf(&byteString[0], format, byte);

    stream() << byteString;
}

void CCodeGenerator::addComment(const std::string &comment)
{
    stream() << " // " << comment << "\n\t";
}

void CCodeGenerator::addLineBreak()
{
    stream() << "\n\t";
}

void CCodeGenerator::endArray()
{
    stream() << "\n};\n";
}

void CCodeGenerator::end()
{
    stream() << "\n\n";
}


ArduinoCodeGenerator::ArduinoCodeGenerator(const SourceCodeOptions &options) :
    CCodeGenerator(options)
{
}

void ArduinoCodeGenerator::begin()
{
    CCodeGenerator::begin();
    stream() << "\n#include <Arduino.h>\n";
}

void ArduinoCodeGenerator::beginArray(const std::string &name)
{
    stream() << "\n\nconst uint8_t " << name << "[] PROGMEM = {\n\t";
}

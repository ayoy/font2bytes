#include "sourcecodegenerator.h"
#include <ctime>

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

std::string SourceCodeGenerator::getCurrentTimestamp() const
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[22];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d/%m/%Y at %H:%M:%S", &tstruct);

    return buf;
}

uint8_t SourceCodeGenerator::formatByte(uint8_t byte) const
{
    if (options.bitNumbering == SourceCodeOptions::MSB) {
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
    return byte;
}

void SourceCodeGenerator::beginArrayRow()
{
    stream() << "\t";
}

void SourceCodeGenerator::addLineBreak()
{
    stream() << "\n";
}

void SourceCodeGenerator::end()
{
    stream() << "\n\n";
}


CCodeGenerator::CCodeGenerator(const SourceCodeOptions &options) :
    SourceCodeGenerator(options)
{
}

void CCodeGenerator::begin()
{
    stream().flush();
    stream() << "//\n// Font Data\n// Created: " << getCurrentTimestamp() << "\n//\n";
}

void CCodeGenerator::beginArray(const std::string &name)
{
    stream() << "\n\nconst unsigned char " << name << "[] = {\n";
}

void CCodeGenerator::writeByte(uint8_t byte)
{
    uint8_t formattedByte = formatByte(byte);

    auto format = "0x%02X,";
    std::string byteString(5, '\0');
    std::sprintf(&byteString[0], format, formattedByte);

    stream() << byteString;
}

void CCodeGenerator::addComment(const std::string &comment)
{
    stream() << " // " << comment;
}

void CCodeGenerator::endArray()
{
    stream() << "};\n";
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
    stream() << "\n\nconst uint8_t " << name << "[] PROGMEM = {\n";
}


PythonListCodeGenerator::PythonListCodeGenerator(const SourceCodeOptions &options) :
    SourceCodeGenerator(options)
{
}

void PythonListCodeGenerator::begin()
{
    stream().flush();
    stream() << "#\n# Font Data\n# Created: " << getCurrentTimestamp() << "\n#\n";
}

void PythonListCodeGenerator::beginArray(const std::string &name)
{
    stream() << "\n\n" << name << " = [\n";
}

void PythonListCodeGenerator::writeByte(uint8_t byte)
{
    uint8_t formattedByte = formatByte(byte);

    auto format = "0x%02X,";
    std::string byteString(5, '\0');
    std::sprintf(&byteString[0], format, formattedByte);

    stream() << byteString;
}

void PythonListCodeGenerator::addComment(const std::string &comment)
{
    stream() << " # " << comment;
}

void PythonListCodeGenerator::endArray()
{
    stream() << "\n]\n";
}


PythonBytesCodeGenerator::PythonBytesCodeGenerator(const SourceCodeOptions &options) :
    SourceCodeGenerator(options)
{
}

void PythonBytesCodeGenerator::begin()
{
    stream().flush();
    stream() << "#\n# Font Data\n# Created: " << getCurrentTimestamp() << "\n#\n";
}

void PythonBytesCodeGenerator::beginArray(const std::string &name)
{
    stream() << "\n\n" << name << " = b'' \\\n";
}

void PythonBytesCodeGenerator::beginArrayRow()
{
    stream() << "\t'";
}

void PythonBytesCodeGenerator::writeByte(uint8_t byte)
{
    uint8_t formattedByte = formatByte(byte);

    auto format = "\\x%02X";
    std::string byteString(4, '\0');
    std::sprintf(&byteString[0], format, formattedByte);

    stream() << byteString;
}

void PythonBytesCodeGenerator::addComment(const std::string &comment)
{
    (void)comment;
    stream() << "' \\";
}

void PythonBytesCodeGenerator::endArray()
{
}

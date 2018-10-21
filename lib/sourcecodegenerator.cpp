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


const std::string CCodeGenerator::identifier = "c";
const std::string CCodeGenerator::description = "C/C++ unsigned char array";

CCodeGenerator::CCodeGenerator(const SourceCodeOptions &options) :
    SourceCodeGenerator(options)
{
}

void CCodeGenerator::begin()
{
    stream().flush();
    stream() << "//\n// Font Data\n// Created: " << getCurrentTimestamp() << "\n//\n";
}

void CCodeGenerator::beginArray(std::string name)
{
    stream() << "\n\nconst unsigned char " << std::move(name) << "[] = {\n";
}

void CCodeGenerator::writeByte(uint8_t byte)
{
    uint8_t formattedByte = formatByte(byte);

    auto format = "0x%02X,";
    std::string byteString(5, '\0');
    std::sprintf(&byteString[0], format, formattedByte);

    stream() << byteString;
}

void CCodeGenerator::addComment(std::string comment)
{
    stream() << " // " << std::move(comment);
}

void CCodeGenerator::endArray()
{
    stream() << "};\n";
}


const std::string ArduinoCodeGenerator::identifier = "arduino";
const std::string ArduinoCodeGenerator::description = "Arduino-compatible array";

ArduinoCodeGenerator::ArduinoCodeGenerator(const SourceCodeOptions &options) :
    CCodeGenerator(options)
{
}

void ArduinoCodeGenerator::begin()
{
    CCodeGenerator::begin();
    stream() << "\n#include <Arduino.h>\n";
}

void ArduinoCodeGenerator::beginArray(std::string name)
{
    stream() << "\n\nconst uint8_t " << std::move(name) << "[] PROGMEM = {\n";
}


const std::string PythonListCodeGenerator::identifier = "pylist";
const std::string PythonListCodeGenerator::description = "Python list";

PythonListCodeGenerator::PythonListCodeGenerator(const SourceCodeOptions &options) :
    SourceCodeGenerator(options)
{
}

void PythonListCodeGenerator::begin()
{
    stream().flush();
    stream() << "#\n# Font Data\n# Created: " << getCurrentTimestamp() << "\n#\n";
}

void PythonListCodeGenerator::beginArray(std::string name)
{
    stream() << "\n\n" << std::move(name) << " = [\n";
}

void PythonListCodeGenerator::writeByte(uint8_t byte)
{
    uint8_t formattedByte = formatByte(byte);

    auto format = "0x%02X,";
    std::string byteString(5, '\0');
    std::sprintf(&byteString[0], format, formattedByte);

    stream() << byteString;
}

void PythonListCodeGenerator::addComment(std::string comment)
{
    stream() << " # " << std::move(comment);
}

void PythonListCodeGenerator::endArray()
{
    stream() << "\n]\n";
}


const std::string PythonBytesCodeGenerator::identifier = "pybytes";
const std::string PythonBytesCodeGenerator::description = "Python bytes object";

PythonBytesCodeGenerator::PythonBytesCodeGenerator(const SourceCodeOptions &options) :
    SourceCodeGenerator(options)
{
}

void PythonBytesCodeGenerator::begin()
{
    stream().flush();
    stream() << "#\n# Font Data\n# Created: " << getCurrentTimestamp() << "\n#\n";
}

void PythonBytesCodeGenerator::beginArray(std::string name)
{
    stream() << "\n\n" << std::move(name) << " = b'' \\\n";
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

void PythonBytesCodeGenerator::addComment(std::string comment)
{
    (void)comment;
    stream() << "' \\";
}

void PythonBytesCodeGenerator::endArray()
{
}

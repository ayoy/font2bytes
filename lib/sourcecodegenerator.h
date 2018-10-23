#ifndef SOURCECODEGENERATOR_H
#define SOURCECODEGENERATOR_H

#include "bytewriter.h"
#include <sstream>

struct SourceCodeOptions
{
    enum BitNumbering { LSB, MSB };


    SourceCodeOptions() {}
    SourceCodeOptions(BitNumbering bitNumbering, bool shouldInvertBits) :
        bitNumbering(bitNumbering),
        shouldInvertBits(shouldInvertBits)
    {}

    BitNumbering bitNumbering { LSB };
    bool shouldInvertBits { false };
};


class SourceCodeGenerator : public ByteWriter
{
public:
    SourceCodeGenerator(SourceCodeOptions options);
    virtual ~SourceCodeGenerator() = default;

    inline std::string sourceCode() { return m_stream->str(); }

    virtual void beginArrayRow() override;
    virtual void addLineBreak() override;
    virtual void end() override;

protected:
    inline std::ostringstream &stream() { return *(m_stream.get()); }
    const SourceCodeOptions options;

    std::string getCurrentTimestamp() const;
    uint8_t formatByte(uint8_t byte) const;

private:
    std::unique_ptr<std::ostringstream> m_stream;
};


class CCodeGenerator : public SourceCodeGenerator
{
public:
    static const std::string identifier;
    static const std::string description;

    CCodeGenerator(SourceCodeOptions options);

    virtual void begin() override;
    virtual void beginArray(std::string name) override;
    virtual void writeByte(uint8_t byte) override;
    virtual void addComment(std::string comment) override;
    virtual void endArray() override;
};


class ArduinoCodeGenerator : public CCodeGenerator
{
public:
    static const std::string identifier;
    static const std::string description;

    ArduinoCodeGenerator(SourceCodeOptions options);

    virtual void begin() override;
    virtual void beginArray(std::string name) override;
};


class PythonListCodeGenerator : public SourceCodeGenerator
{
public:
    static const std::string identifier;
    static const std::string description;

    PythonListCodeGenerator(SourceCodeOptions options);

    virtual void begin() override;
    virtual void beginArray(std::string name) override;
    virtual void writeByte(uint8_t byte) override;
    virtual void addComment(std::string comment) override;
    virtual void endArray() override;
};

class PythonBytesCodeGenerator : public SourceCodeGenerator
{
public:
    static const std::string identifier;
    static const std::string description;

    PythonBytesCodeGenerator(SourceCodeOptions options);

    virtual void begin() override;
    virtual void beginArray(std::string name) override;
    virtual void beginArrayRow() override;
    virtual void writeByte(uint8_t byte) override;
    virtual void addComment(std::string comment) override;
    virtual void endArray() override;
};

#endif // SOURCECODEGENERATOR_H

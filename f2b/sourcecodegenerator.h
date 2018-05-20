#ifndef SOURCECODEGENERATOR_H
#define SOURCECODEGENERATOR_H

#include "bytewriter.h"
#include <sstream>

struct SourceCodeOptions
{
    enum BitNumbering { LSB, MSB };

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
    SourceCodeGenerator(const SourceCodeOptions &options);
    virtual ~SourceCodeGenerator();

    inline std::string sourceCode() { return m_stream->str(); }

    virtual void beginArrayRow() override;
    virtual void addLineBreak() override;
    virtual void end() override;

protected:
    inline std::ostringstream &stream() { return *m_stream; }
    const SourceCodeOptions options;

    std::string getCurrentTimestamp() const;
    uint8_t formatByte(uint8_t byte) const;

private:
    std::ostringstream *m_stream;
};


class CCodeGenerator : public SourceCodeGenerator
{
public:
    CCodeGenerator(const SourceCodeOptions &options);

    virtual void begin() override;
    virtual void beginArray(const std::string &name) override;
    virtual void writeByte(uint8_t byte) override;
    virtual void addComment(const std::string &comment) override;
    virtual void endArray() override;
};


class ArduinoCodeGenerator : public CCodeGenerator
{
public:
    ArduinoCodeGenerator(const SourceCodeOptions &options);

    virtual void begin() override;
    virtual void beginArray(const std::string &name) override;
};


class PythonListCodeGenerator : public SourceCodeGenerator
{
public:
    PythonListCodeGenerator(const SourceCodeOptions &options);

    virtual void begin() override;
    virtual void beginArray(const std::string &name) override;
    virtual void writeByte(uint8_t byte) override;
    virtual void addComment(const std::string &comment) override;
    virtual void endArray() override;
};

class PythonBytesCodeGenerator : public SourceCodeGenerator
{
public:
    PythonBytesCodeGenerator(const SourceCodeOptions &options);

    virtual void begin() override;
    virtual void beginArray(const std::string &name) override;
    virtual void beginArrayRow() override;
    virtual void writeByte(uint8_t byte) override;
    virtual void addComment(const std::string &comment) override;
    virtual void endArray() override;
};

#endif // SOURCECODEGENERATOR_H

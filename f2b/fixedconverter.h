#ifndef FIXEDCONVERTER_H
#define FIXEDCONVERTER_H

#include "fontconverter.h"
#include <cstdint>

class FixedConverter : public FontConverter
{
public:
    FixedConverter(uint8_t width, uint8_t height, ReadingMode readingMode);
    virtual ~FixedConverter();

    virtual ConverterError convert(const InputImage &image, ByteWriter *byteWriter) override;

protected:
    virtual ConverterError checkImage(const InputImage &image);

private:
    uint8_t m_width;
    uint8_t m_height;
    ReadingMode m_readingMode;
};

#endif // FIXEDCONVERTER_H

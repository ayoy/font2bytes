#ifndef FONTCONVERTER_H
#define FONTCONVERTER_H

#include "inputimage.h"
#include "bytewriter.h"
#include "convertererror.h"

class FontConverter
{
public:
    virtual ConverterError convert(const InputImage &image, ByteWriter *byteWriter) = 0;

    enum ReadingMode { TopToBottom, LeftToRight };
};

#endif // FONTCONVERTER_H

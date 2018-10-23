#ifndef FONTCONVERTER_H
#define FONTCONVERTER_H

#include "inputimage.h"
#include "bytewriter.h"
#include "convertererror.h"

class FontConverter
{
public:
    virtual ConverterError convert(const InputImage &image, ByteWriter &byteWriter) = 0;

    /**
     * @brief The direction of the conversion
     */
    enum ReadingMode {
        TopToBottom, /// Each character from top to bottom.
        LeftToRight  /// Each character from left to right.
    };
};

#endif // FONTCONVERTER_H

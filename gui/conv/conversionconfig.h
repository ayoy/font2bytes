#ifndef CONVERSIONCONFIG_H
#define CONVERSIONCONFIG_H

#include <cstdint>
#include <f2b.h>

struct ConversionConfig
{
    uint8_t fontWidth = 0;
    uint8_t fontHeight = 0;
    bool shouldInvertBits = false;
    SourceCodeOptions::BitNumbering bitNumbering = SourceCodeOptions::LSB;
    FixedWidthFontConverter::ReadingMode readingMode = FixedWidthFontConverter::TopToBottom;

    int sourceCodeGeneratorIndex = 0;

    void loadFromSettings();
    void saveToSettings() const;

    inline bool isHeightValid() const {
        return fontHeight >= 1;
    }

    inline bool isWidthValid() const {
        return fontWidth >= 1;
    }

    inline bool isValid() const {
        return isHeightValid() and isWidthValid();
    }
};

#endif // CONVERSIONCONFIG_H

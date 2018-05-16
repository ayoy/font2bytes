#ifndef CONVERSIONCONFIG_H
#define CONVERSIONCONFIG_H

struct ConversionConfig
{
    enum ReadingMode { TopToBottom, LeftToRight };
    enum BitNumbering { LSB, MSB };

    uint8_t fontWidth = 0;
    uint8_t fontHeight = 0;
    bool shouldInvertBits = false;
    BitNumbering bitNumbering = LSB;
    ReadingMode readingMode = TopToBottom;

    inline bool isHeightValid() const {
        return fontHeight >= 8;
    }

    inline bool isWidthValid() const {
        return fontWidth >= 8;
    }

    inline bool isValid() const {
        return isHeightValid() and isWidthValid();
    }
};

#endif // CONVERSIONCONFIG_H

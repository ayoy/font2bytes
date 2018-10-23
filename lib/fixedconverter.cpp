#include "fixedconverter.h"

FixedConverter::FixedConverter(uint8_t width, uint8_t height, ReadingMode readingMode) :
    m_width(width),
    m_height(height),
    m_readingMode(readingMode)
{
}

FixedConverter::~FixedConverter()
{
}

ConverterError FixedConverter::checkImage(const InputImage &image)
{
    if (image.width() < m_width) {
        return ConverterError("Image Too Small",
                              "The width of the image has to be minimum " + std::to_string(m_width) + " pixels.");
    }
    if (image.height() < m_height) {
        return ConverterError("Image Too Small",
                              "The height of the image has to be minimum " + std::to_string(m_height) + " pixels.");
    }
    if (image.width() % m_width != 0) {
        return ConverterError("Odd Image Height",
                              "The height of the image has to be a multiple of " + std::to_string(m_height) + " pixels.");
    }
    if (image.height() % m_height != 0) {
        return ConverterError("Odd Image Height",
                              "The height of the image has to be a multiple of " + std::to_string(m_height) + " pixels.");
    }
    if (image.width() > 256*m_width || image.height() > 256*m_height) {
        return ConverterError("Image Too Large",
                              "The image dimensions must not be greater than 256 times font dimensions.");
    }
    return ConverterError::NoError;
}

ConverterError FixedConverter::convert(const InputImage &image, ByteWriter &byteWriter)
{
    auto checkResult = checkImage(image);
    if (checkResult != ConverterError::NoError) {
        return checkResult;
    }

    byteWriter.begin();
    byteWriter.beginArray("font");

    int characterCount = 0;
    for (uint8_t y = 0; y < image.height()/m_height; y++) {
        for (uint8_t x = 0; x < image.width()/m_width; x++) {
            byteWriter.beginArrayRow();
            for (uint8_t row = 0; row < m_height; row++) {
                uint8_t remainingBits = m_width;

                // for width > 8, each line will be represented by more than one byte;
                // let's track bytes count per line here
                uint8_t byteIndex = 0;

                while (remainingBits > 0) {
                    uint8_t byte = 0;
                    uint8_t bitCount = std::min(remainingBits, (uint8_t)8);
                    uint8_t mask = 1<<7;
                    for (uint8_t bit = 0; bit < bitCount; bit++) {
                        switch (m_readingMode) {
                            case TopToBottom:
                                if (image.isPixelSet(x*m_width+bit+8*byteIndex, y*m_height+row)) {
                                    byte |= mask;
                                }
                                break;
                            case LeftToRight:
                                if (image.isPixelSet(x*m_height+row, y*m_width+bit+8*byteIndex)) {
                                    byte |= mask;
                                }
                                break;
                        }
                        mask >>= 1;
                        remainingBits -= 1;
                    }
                    byteWriter.writeByte(byte);
                    byteIndex += 1;
                }
            }
            auto format = "Character 0x%02X (%d)";
            auto size = std::snprintf(nullptr, 0, format, characterCount, characterCount);
            std::string byteString(size, '\0');
            std::sprintf(&byteString[0], format, characterCount, characterCount);
            byteWriter.addComment(byteString);
            byteWriter.addLineBreak();
            characterCount += 1;
        }
    }
    byteWriter.endArray();
    byteWriter.end();


    return ConverterError::NoError;
}

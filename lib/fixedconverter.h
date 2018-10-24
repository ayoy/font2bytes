#ifndef FIXEDCONVERTER_H
#define FIXEDCONVERTER_H

#include "fontconverter.h"
#include <cstdint>

/**
 * @brief A simple converter which converts fixed-width fonts.
 *
 * Starting from the top-left 8x8 block, it converts each block from
 * left to right, from top to down.
 *
 * For 'w' width and 'h' height, each w x h block is converted to the total
 * amount of h*(Int(w/8)+1) bytes, i.e. each row is represented by Int(w/8)+1 bytes,
 * so:
 *
 *   width | bytes
 *  ---------------
 *     5   |   1
 *     7   |   1
 *     8   |   1
 *    12   |   2
 *    16   |   2
 *    19   |   3
 *
 * The left bit is the highest bit, and the first byte in a row is a leftmost byte.
 * Unused trailing bits are zeroed.
 * Example:
 * 'A' (17 pixels wide)
 * ...######........ -> 0x1F, 0x80, 0x00
 * ...#######....... -> 0x1F, 0xC0, 0x00
 * .......###....... -> 0x01, 0xC0, 0x00
 * ......##.##...... -> 0x03, 0x60, 0x00
 * ......##.##...... -> 0x03, 0x60, 0x00
 * .....##...##..... -> 0x06, 0x30, 0x00
 * .....##...##..... -> 0x06, 0x30, 0x00
 * ....##....##..... -> 0x0C, 0x30, 0x00
 * ....#########.... -> 0x0F, 0xF8, 0x00
 * ...##########.... -> 0x1F, 0xF8, 0x00
 * ...##.......##... -> 0x18, 0x0C, 0x00
 * ..##........##... -> 0x30, 0x0C, 0x00
 * ######...#######. -> 0xFC, 0x7F, 0x00
 * ######...#######. -> 0xFC, 0x7F, 0x00
 * ................. -> 0x00, 0x00, 0x00
 *
 * This char will result in the byte sequence: 0x1F, 0x80, 0x00, 0x1F, 0xC0, 0x00, ...
 *
 * '9' (8 pixels wide)
 * ..XXXX.. -> 0x3C
 * .XX..XX. -> 0x66
 * .XX..XX. -> 0x66
 * ..XXXXX. -> 0x3E
 * .....XX. -> 0x06
 * .....XX. -> 0x06
 * .XX..XX. -> 0x66
 * ..XXXX.. -> 0x3C
 * ........ -> 0x00
 *
 * This char will result in the byte sequence: 0x3c, 0x66, 0x66, ...
 *
 */
class FixedConverter : public FontConverter
{
public:
    FixedConverter(uint8_t width, uint8_t height, ReadingMode readingMode);
    virtual ~FixedConverter() = default;

    virtual ConverterError convert(const InputImage &image, ByteWriter &byteWriter) override;

protected:
    virtual ConverterError checkImage(const InputImage &image);

private:
    uint8_t m_width;
    uint8_t m_height;
    ReadingMode m_readingMode;
};

#endif // FIXEDCONVERTER_H

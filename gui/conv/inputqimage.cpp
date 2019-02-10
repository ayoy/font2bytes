#include "inputqimage.h"

InputQImage::InputQImage(const QImage &image):
    InputImage(),
    image { image }
{
}

InputQImage::~InputQImage()
{
}

uint32_t InputQImage::width() const
{
    return image.width();
}

uint32_t InputQImage::height() const
{
    return image.height();
}

bool InputQImage::isPixelSet(uint32_t x, uint32_t y) const
{
    if (x > width() || y > height()) {
        return false;
    }

    QRgb pixel = image.pixel(x, y);

    if (qAlpha(pixel) < 0xFF) {
        return false;
    }

    return (qRed(pixel) < 0x32 || qGreen(pixel) < 0x32 || qBlue(pixel) < 0x32);
}

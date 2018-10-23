#include "inputpngimage.h"

InputPNGImage::~InputPNGImage()
{
    png_data_destroy(data.get());
}

bool InputPNGImage::isPixelSet(uint32_t x, uint32_t y) const
{
    if (x > width() || y > height()) {
        return false;
    }

    png_bytep pixel = &(data->row_pointers[y][x*4]);

    // require 100% alpha
    if (pixel[3] < 0xFF) {
        return false;
    }

    return pixel[0] < 0x32 || pixel[1] < 0x32 || pixel[2] < 0x32;
}

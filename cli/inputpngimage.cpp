#include "inputpngimage.h"
#include <iostream>
#include <cerrno>

std::optional<InputPNGImage> InputPNGImage::construct(const std::string &filePath)
{
    png_data *data = png_data_create(filePath.c_str());
    if (data == nullptr) {
        std::cerr << "Failed to read PNG file at " << filePath << ": " << strerror(errno) << std::endl;
        return std::nullopt;
    }
    return InputPNGImage(data);
}

bool InputPNGImage::isPixelSet(uint32_t x, uint32_t y) const
{
    if (x > width() || y > height()) {
        return false;
    }

    png_bytep pixel = &(_data->row_pointers[y][x*4]);

    // require 100% alpha
    if (pixel[3] < 0xFF) {
        return false;
    }

    return pixel[0] < 0x32 || pixel[1] < 0x32 || pixel[2] < 0x32;
}

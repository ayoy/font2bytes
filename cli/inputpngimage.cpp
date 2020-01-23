#include "inputpngimage.h"
#include <iostream>
#include <cerrno>
#include <cstring>

static constexpr int pixel_byte_size = 4;

bool Pixel::is_set() const {
    return a == 0xFF &&
           (r < is_set_threshold ||
            g < is_set_threshold ||
            b < is_set_threshold);
}

std::optional<Pixel> Pixel::from_span(const gsl::span<png_byte>& s)
{
    if (s.size() < pixel_byte_size) {
        std::cerr << "Invalid span size for Pixel: " << s.size() << std::endl;
        return std::nullopt;
    }
    return Pixel { .r = s[0], .g = s[1], .b = s[2], .a = s[3] };
}


std::optional<InputPNGImage> InputPNGImage::construct(const std::string& filePath)
{
    png_data *data = png_data_create(filePath.c_str());
    if (data == nullptr) {
        std::cerr << "Failed to read PNG file at " << filePath
                  << ": " << std::strerror(errno) << std::endl;
        return std::nullopt;
    }

    std::vector<bool> pixels;

    for (uint32_t row = 0; row < data->height; row++) {

        auto raw_image_row = data->row_pointers[static_cast<size_t>(row)];
        gsl::span<png_byte> image_row(raw_image_row, data->width * pixel_byte_size);

        auto i = image_row.begin();
        while (i != image_row.end()) {

            auto pixel = Pixel::from_span(gsl::span(&(*i), pixel_byte_size));
            if (!pixel.has_value()) {
                std::cerr << "Failed to read PNG byte in row " << row << std::endl;
                png_data_destroy(data);
                return std::nullopt;
            }
            pixels.push_back(pixel->is_set());
            i += pixel_byte_size;

        }
    }
    auto width = data->width;
    auto height = data->height;
    png_data_destroy(data);
    return InputPNGImage(std::move(pixels), width, height);
}

InputPNGImage::InputPNGImage(std::vector<bool>&& pixels, uint32_t width, uint32_t height) :
        InputImage(),
        _width { width },
        _height { height },
        _data { pixels }
{
}

bool InputPNGImage::isPixelSet(uint32_t x, uint32_t y) const
{
    if (x > width() || y > height()) {
        return false;
    }
    return bool(_data[y * _width + x]);
}

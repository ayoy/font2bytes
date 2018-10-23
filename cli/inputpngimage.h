#ifndef INPUTPNGIMAGE_H
#define INPUTPNGIMAGE_H

#include <f2b.h>
#include <memory>
#include <optional>
#include <iostream>
#include "png_read.h"

class InputPNGImage : public InputImage
{
public:
    static std::optional<InputPNGImage> construct(const std::string &filePath);

    virtual ~InputPNGImage() = default;

    InputPNGImage(InputPNGImage &&other):
            InputImage(),
            _data{std::exchange(other._data, nullptr)} {}

    InputPNGImage& operator=(InputPNGImage &&other) {
        _data = std::exchange(other._data, nullptr);
        return *this;
    }

    InputPNGImage(const InputPNGImage &other) = delete;
    InputPNGImage& operator=(const InputPNGImage &other) = delete;

    virtual uint32_t width() const override { return _data->width; }
    virtual uint32_t height() const override { return _data->height; }
    virtual bool isPixelSet(uint32_t x, uint32_t y) const override;

private:
    InputPNGImage(png_data *data): InputImage(), _data{data, &png_data_destroy} {}

    std::unique_ptr<png_data, decltype(&png_data_destroy)> _data;
};

#endif // INPUTPNGIMAGE_H

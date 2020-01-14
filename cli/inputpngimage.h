#ifndef INPUTPNGIMAGE_H
#define INPUTPNGIMAGE_H

#include <f2b.h>
#include <memory>
#include <optional>
#include <iostream>
#include <vector>
#include <include/gsl/span>
#include "png_read.h"

struct Pixel {
    png_byte r;
    png_byte g;
    png_byte b;
    png_byte a;

    static std::optional<Pixel> from_span(const gsl::span<png_byte> &s);

    bool is_set() const;
    const uint8_t is_set_threshold = 0x32;
};

class InputPNGImage : public InputImage
{
public:
    static std::optional<InputPNGImage> construct(const std::string &filePath);

    virtual ~InputPNGImage() override = default;
    InputPNGImage(InputPNGImage &&other) = default;
    InputPNGImage& operator=(InputPNGImage &&other) = default;

    InputPNGImage(const InputPNGImage &other) = delete;
    InputPNGImage& operator=(const InputPNGImage &other) = delete;

    virtual uint32_t width() const override { return _width; }
    virtual uint32_t height() const override { return _height; }
    virtual bool isPixelSet(uint32_t x, uint32_t y) const override;

private:
    InputPNGImage(std::vector<Pixel> pixels, uint32_t width, uint32_t height);

    uint32_t _width;
    uint32_t _height;
    std::vector<Pixel> _data;
};

#endif // INPUTPNGIMAGE_H

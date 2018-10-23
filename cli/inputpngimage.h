#ifndef INPUTPNGIMAGE_H
#define INPUTPNGIMAGE_H

#include <f2b.h>
#include <memory>
#include "png_read.h"

class InputPNGImage : public InputImage
{
public:
    InputPNGImage(std::unique_ptr<png_data> data): InputImage(), data(std::move(data)) {}
    virtual ~InputPNGImage();

    virtual uint32_t width() const override { return data->width; }
    virtual uint32_t height() const override { return data->height; }
    virtual bool isPixelSet(uint32_t x, uint32_t y) const override;

private:
    std::unique_ptr<png_data> data;
};

#endif // INPUTPNGIMAGE_H

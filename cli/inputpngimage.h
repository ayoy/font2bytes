#ifndef INPUTPNGIMAGE_H
#define INPUTPNGIMAGE_H

#include <f2b.h>
#include "png_read.h"

class InputPNGImage : public InputImage
{
public:
    InputPNGImage(png_data *data);
    virtual ~InputPNGImage();

    virtual uint32_t width() const override;
    virtual uint32_t height() const override;
    virtual bool isPixelSet(uint32_t x, uint32_t y) const override;

private:
    png_data *data;
};

#endif // INPUTPNGIMAGE_H

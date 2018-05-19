#ifndef INPUTQIMAGE_H
#define INPUTQIMAGE_H

#include "inputimage.h"
#include <QImage>

class InputQImage : public InputImage
{
public:
    InputQImage(const QImage &image);
    virtual ~InputQImage();

    uint32_t width() const override;
    uint32_t height() const override;
    bool isPixelSet(uint32_t x, uint32_t y) const override;

private:
    QImage image;
};

#endif // INPUTQIMAGE_H

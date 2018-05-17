#include "imageconverter.h"

ImageConverter::ImageConverter(QObject *parent) : QObject(parent)
{

}

QString ImageConverter::convertImage(const QImage &image, bool *ok)
{
    return QString();
}

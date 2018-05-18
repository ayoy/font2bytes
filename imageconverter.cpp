#include "imageconverter.h"

ImageConverter::ImageConverter(QObject *parent) : QObject(parent)
{

}

QString ImageConverter::convertImage(bool *ok)
{
    if (ok) {
        *ok = true;
    }
    return QString();
}

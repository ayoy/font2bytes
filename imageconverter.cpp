#include "imageconverter.h"
#include "fixedconverter.h"
#include "inputqimage.h"

ImageConverter::ImageConverter(QObject *parent) : QObject(parent)
{
}

ImageConverter::~ImageConverter()
{
    if (m_image) {
        delete m_image;
        m_image = nullptr;
    }
    if (m_sourceCodeGenerator) {
        delete m_sourceCodeGenerator;
        m_sourceCodeGenerator = nullptr;
    }
}

QString ImageConverter::convert(bool *ok)
{
    bool success = false;
    if (!m_image) {
        m_error = "Input image not provided";
        return QString();
    }
    if (!m_sourceCodeGenerator) {
        m_error = "Source code generator not provided";
        return QString();
    }

    FixedConverter converter(m_config.fontWidth, m_config.fontHeight, m_config.readingMode);
    converter.convert(*m_image, m_sourceCodeGenerator);

    QString result = QString::fromStdString(m_sourceCodeGenerator->sourceCode());

    success = result.count() > 0;
    if (ok) {
        *ok = success;
    }

    return result;
}

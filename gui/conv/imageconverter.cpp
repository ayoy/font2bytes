#include "imageconverter.h"
#include <functional>

ImageConverter::ImageConverter(QObject *parent) : QObject(parent)
{
}

ImageConverter::~ImageConverter()
{
    if (m_image) {
        delete m_image;
        m_image = nullptr;
    }
}

QString ImageConverter::convert(bool *ok)
{
    std::function<QString(const QString &)> tearDown = [this, ok](const QString &sourceCode) {
        bool success = this->m_error == ConverterError::NoError;
        if (ok) {
            *ok = success;
        }
        return sourceCode;
    };


    if (m_image == nullptr) {
        m_error = "Input image not provided";
        return tearDown(QString());
    }
    if (m_sourceCodeGenerator == nullptr) {
        m_error = "Source code generator not provided";
        return tearDown(QString());
    }

    FixedWidthFontConverter converter(m_config.fontWidth,
                                      m_config.fontHeight,
                                      m_config.readingMode,
                                      std::move(m_sourceCodeGenerator));
    auto sourceCode = converter.convert(*m_image, &m_error);

    QString result = QString::fromStdString(sourceCode);

    return tearDown(result);
}

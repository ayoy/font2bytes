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
    if (m_sourceCodeGenerator) {
        delete m_sourceCodeGenerator;
        m_sourceCodeGenerator = nullptr;
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


    if (!m_image) {
        m_error = "Input image not provided";
        return tearDown(QString());
    }
    if (!m_sourceCodeGenerator) {
        m_error = "Source code generator not provided";
        return tearDown(QString());
    }

    FixedConverter converter(m_config.fontWidth, m_config.fontHeight, m_config.readingMode);
    m_error = converter.convert(*m_image, m_sourceCodeGenerator);

    QString result = QString::fromStdString(m_sourceCodeGenerator->sourceCode());

    return tearDown(result);
}

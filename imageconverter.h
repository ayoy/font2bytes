#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include <QObject>
#include <QImage>
#include "convertererror.h"
#include "conversionconfig.h"
#include "bytewriter.h"
#include "inputqimage.h"

class ImageConverter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(InputQImage * image READ image WRITE setImage)
    Q_PROPERTY(SourceCodeGenerator * sourceCodeGenerator READ sourceCodeGenerator WRITE setSourceCodeGenerator)
    Q_PROPERTY(ConversionConfig config READ config WRITE setConfig)
    Q_PROPERTY(ConverterError error READ error)

public:

    explicit ImageConverter(QObject *parent = nullptr);
    virtual ~ImageConverter();

    QString convert(bool *ok = nullptr);

    inline InputQImage *image() const { return m_image; }
    inline void setImage(InputQImage *image) { m_image = image; }

    inline SourceCodeGenerator * sourceCodeGenerator() const { return m_sourceCodeGenerator; }
    inline void setSourceCodeGenerator(SourceCodeGenerator *sourceCodeGenerator) { m_sourceCodeGenerator = sourceCodeGenerator; }

    inline ConversionConfig config() const { return m_config; }
    inline void setConfig(const ConversionConfig &config) { m_config = config; }

    inline ConverterError error() const { return m_error; }

signals:
    void conversionFinished();

private:
    SourceCodeGenerator *m_sourceCodeGenerator;
    InputQImage *m_image;
    ConversionConfig m_config;
    ConverterError m_error;
};

#endif // IMAGECONVERTER_H

#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include <QObject>
#include <QImage>
#include <f2b.h>
#include "inputqimage.h"
#include "conversionconfig.h"

class ImageConverter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(InputQImage * image READ image WRITE setImage)
    Q_PROPERTY(ConversionConfig config READ config WRITE setConfig)
    Q_PROPERTY(ConverterError error READ error)
    Q_PROPERTY(SourceCodeGeneratorInterface * sourceCodeGenerator READ sourceCodeGenerator WRITE setSourceCodeGenerator)

public:

    explicit ImageConverter(QObject *parent = nullptr);
    virtual ~ImageConverter();

    QString convert(bool *ok = nullptr);

    inline InputQImage *image() const { return m_image; }
    inline void setImage(InputQImage *image) { m_image = image; }

    inline ConversionConfig config() const { return m_config; }
    inline void setConfig(const ConversionConfig &config) { m_config = config; }

    inline ConverterError error() const { return m_error; }

    inline SourceCodeGeneratorInterface * sourceCodeGenerator() const {
        return m_sourceCodeGenerator.get();
    }

    inline void setSourceCodeGenerator(SourceCodeGeneratorInterface * sourceCodeGenerator) {
        m_sourceCodeGenerator = std::unique_ptr<SourceCodeGeneratorInterface>(sourceCodeGenerator);
    }

signals:
    void conversionFinished(const QString &sourceCode, const ConverterError &error);

private:
    InputQImage *m_image;
    ConversionConfig m_config;
    ConverterError m_error;
    std::unique_ptr<SourceCodeGeneratorInterface> m_sourceCodeGenerator;
};

#endif // IMAGECONVERTER_H

#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include <QObject>
#include <QImage>
#include "conversionconfig.h"

class ImageConverter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ConversionConfig config READ config WRITE setConfig)
    Q_PROPERTY(ConversionError error READ error)

public:
    enum ConversionError { NoError, ImageLoadingError };
    Q_ENUM(ConversionError)

    explicit ImageConverter(QObject *parent = nullptr);
    QString convertImage(const QImage &image, bool *ok = nullptr);


    inline ConversionConfig config() const {
        return m_config;
    }
    inline void setConfig(const ConversionConfig &config) {
        m_config = config;
    }
    inline ConversionError error() const {
        return m_error;
    }

private:
    ConversionConfig m_config;
    ConversionError m_error { NoError };
};

#endif // IMAGECONVERTER_H

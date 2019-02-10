#ifndef CONVERSIONSERVICE_H
#define CONVERSIONSERVICE_H

#include <QObject>
#include <QElapsedTimer>
#include <QMap>
#include <f2b.h>
#include "conversionconfig.h"
#include "sourcecodegenerator.h"

class ConversionRunnable;

struct SourceCodeGeneratorItem {
    friend class ConversionService;

    QString title;

private:
    std::function<SourceCodeGeneratorInterface * (const SourceCodeOptions &options)> createGenerator;
};

class ConversionService: public QObject
{
    Q_OBJECT
    Q_PROPERTY(ConversionConfig config READ config WRITE setConfig)
    Q_PROPERTY(QList<SourceCodeGeneratorItem> generators READ generators)

public:

    explicit ConversionService(QObject *parent = nullptr);
    virtual ~ConversionService();

    inline ConversionConfig config() const { return m_config; }
    inline void setConfig(const ConversionConfig &config) { m_config = config; }

    inline QList<SourceCodeGeneratorItem> generators() const { return m_generators; }

    void convert(const QImage &image, const SourceCodeGeneratorItem &generatorItem);

signals:
    void conversionComplete(const QString &sourceCode, const ConverterError &error, qint64 elapsedTime);

private slots:
    void handleConversionFinished(const QString &sourceCode, const ConverterError &error);

private:
    void populateSourceCodeGenerators();

    ConversionConfig m_config;
    ConversionRunnable *m_conversion { nullptr };
    QElapsedTimer m_conversionTimer;
    QList<SourceCodeGeneratorItem> m_generators;
};

#endif // CONVERSIONSERVICE_H

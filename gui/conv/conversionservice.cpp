#include "conversionservice.h"
#include "conversionrunnable.h"
#include <QThreadPool>

ConversionService::ConversionService(QObject * parent) :
    QObject(parent)
{
    populateSourceCodeGenerators();
    m_config.loadFromSettings();
}

ConversionService::~ConversionService()
{
    m_generators.clear();
    if (m_conversion && !m_conversion->isFinished()) {
        m_conversion->setCanceled(true);
        m_conversion = nullptr;
    }
}

void ConversionService::populateSourceCodeGenerators()
{
    m_generators.clear();
    SourceCodeGeneratorItem cGenerator;
    cGenerator.title = tr("C/C++");
    cGenerator.createGenerator = [](const SourceCodeOptions &options) {
        return new SourceCodeGenerator<CCodeGenerator>(options);
    };
    m_generators << cGenerator;

    SourceCodeGeneratorItem arduinoGenerator;
    arduinoGenerator.title = tr("Arduino");
    arduinoGenerator.createGenerator = [](const SourceCodeOptions &options) {
        return new SourceCodeGenerator<ArduinoCodeGenerator>(options);
    };
    m_generators << arduinoGenerator;

    SourceCodeGeneratorItem pythonListGenerator;
    pythonListGenerator.title = tr("Python List");
    pythonListGenerator.createGenerator = [](const SourceCodeOptions &options) {
        return new SourceCodeGenerator<PythonListCodeGenerator>(options);
    };
    m_generators << pythonListGenerator;

    SourceCodeGeneratorItem pythonBytesGenerator;
    pythonBytesGenerator.title = tr("Python Bytes");
    pythonBytesGenerator.createGenerator = [](const SourceCodeOptions &options) {
        return new SourceCodeGenerator<PythonBytesCodeGenerator>(options);
    };
    m_generators << pythonBytesGenerator;
}

void ConversionService::convert(const QImage &image,
                                const SourceCodeGeneratorItem &generatorItem)
{
    if (m_conversion and !m_conversion->isFinished()) {
        m_conversion->setCanceled(true);
    }

    SourceCodeOptions options(m_config.bitNumbering, m_config.shouldInvertBits);
    auto generator = generatorItem.createGenerator(options);

    m_conversion = new ConversionRunnable();
    m_conversion->imageConverter()->setImage(new InputQImage(image));
    m_conversion->imageConverter()->setSourceCodeGenerator(generator);
    m_conversion->imageConverter()->setConfig(m_config);

    connect(m_conversion->imageConverter(), SIGNAL(conversionFinished(QString,ConverterError)),
            this, SLOT(handleConversionFinished(QString,ConverterError)),
            Qt::BlockingQueuedConnection);

    m_conversionTimer.start();
    QThreadPool::globalInstance()->start(m_conversion);
}

void ConversionService::handleConversionFinished(const QString &sourceCode, const ConverterError &error)
{
    qint64 conversionTime = m_conversionTimer.elapsed();
    m_conversionTimer.invalidate();
    Q_ASSERT(m_conversion->isFinished());
    m_conversion = nullptr;

    emit conversionComplete(sourceCode, error, conversionTime);
}

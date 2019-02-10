#include "conversionrunnable.h"
#include <QThread>
#include <QDebug>
#include <QMutexLocker>

ConversionRunnable::ConversionRunnable() :
    QRunnable(),
    m_imageConverter { new ImageConverter() }
{
}

ConversionRunnable::~ConversionRunnable()
{
    delete m_imageConverter;
    m_imageConverter = nullptr;
}

bool ConversionRunnable::isFinished()
{
    QMutexLocker locker(&instanceMutex);
    return m_finished;
}

void ConversionRunnable::setFinished(bool finished)
{
    QMutexLocker locker(&instanceMutex);
    m_finished = finished;
}

bool ConversionRunnable::isCanceled()
{
    QMutexLocker locker(&instanceMutex);
    return m_canceled;
}

void ConversionRunnable::setCanceled(bool canceled)
{
    QMutexLocker locker(&instanceMutex);
    m_canceled = canceled;
}

void ConversionRunnable::run()
{
    QString sourceCode = m_imageConverter->convert();
    setFinished(true);

    if (!isCanceled()) {
        emit m_imageConverter->conversionFinished(sourceCode, m_imageConverter->error());
    }
}

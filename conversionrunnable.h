#ifndef CONVERSIONRUNNABLE_H
#define CONVERSIONRUNNABLE_H

#include <QRunnable>
#include <QMutex>
#include "imageconverter.h"

class ConversionRunnable : public QRunnable
{
public:
    ConversionRunnable();
    virtual ~ConversionRunnable();

    void run() override;

    inline ImageConverter *imageConverter() const { return m_imageConverter; }
    bool isFinished();

    bool isCanceled();
    void setCanceled(bool canceled);

protected:
    void setFinished(bool finished);

private:
    ImageConverter *m_imageConverter;
    bool m_finished { false };
    bool m_canceled { false };
    QMutex instanceMutex;
};

#endif // CONVERSIONRUNNABLE_H

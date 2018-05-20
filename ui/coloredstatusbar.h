#ifndef COLOREDSTATUSBAR_H
#define COLOREDSTATUSBAR_H

#include <QStatusBar>

class ColoredStatusBar : public QStatusBar
{
    Q_OBJECT

public:
    explicit ColoredStatusBar(QWidget *parent = nullptr);
    virtual ~ColoredStatusBar();

public slots:
    void showMessage(const QString &text, int timeout = 0);
    void showMessage(const QString &text, const QColor &color, int timeout = 0);
};

#endif // COLOREDSTATUSBAR_H

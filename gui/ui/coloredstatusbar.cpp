#include "coloredstatusbar.h"

ColoredStatusBar::ColoredStatusBar(QWidget *parent) :
    QStatusBar(parent)
{
}

ColoredStatusBar::~ColoredStatusBar()
{
}

void ColoredStatusBar::showMessage(const QString &text, int timeout)
{
    showMessage(text, Qt::black, timeout);
}

void ColoredStatusBar::showMessage(const QString &text, const QColor &color, int timeout)
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::WindowText, color);
    setPalette(palette);

    QStatusBar::showMessage(text, timeout);
}

#include "droplabel.h"
#include <QPainter>
#include <QDebug>

DropLabel::DropLabel(QWidget *parent):
    QLabel(parent),
    defaultPalette(palette())
{
    defaultPalette.setColor(QPalette::WindowText, Qt::gray);
    setPalette(defaultPalette);
    setFont(QFont("Helvetica", 42, QFont::Black));
    updateStyleSheet();
    setAutoFillBackground(true);
}

void DropLabel::updateStyleSheet()
{
    qDebug() << __PRETTY_FUNCTION__ << m_dropActionAvailable;
    QPalette palette(this->palette());
    if (m_dropActionAvailable) {
        palette.setColor(backgroundRole(), defaultPalette.color(QPalette::Highlight));
        palette.setColor(foregroundRole(), defaultPalette.color(QPalette::BrightText));
    } else {
        palette.setColor(backgroundRole(), defaultPalette.color(QPalette::Window));
        palette.setColor(foregroundRole(), defaultPalette.color(QPalette::WindowText));
    }
    setPalette(palette);
}

void DropLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int xOffset = 40;
    const int yOffset = 30;
    const qreal cornerRadius = 20.0;

    QFontMetrics fm(font());
    QStringList components = text().split('\n', QString::SkipEmptyParts);
    int maxWidth = 0;
    for (const auto &line : components) {
        maxWidth = qMax(maxWidth, fm.width(line));
    }
    int height = components.count() * fm.height() + (components.count()-1) * fm.leading();

    QPoint topLeft = rect().center();
    topLeft.rx() -= maxWidth/2 + xOffset;
    topLeft.ry() -= height/2 + yOffset;
    QRect rect = QRect(topLeft, QSize(maxWidth + 2 * xOffset, height + 2 * yOffset));

    QPainterPath path;
    path.addRoundedRect(rect, cornerRadius, cornerRadius);

    QPainterPathStroker stroker;
    stroker.setDashPattern(QVector<qreal>() << 1 << 2);
    stroker.setWidth(8);

    painter.fillPath(stroker.createStroke(path), palette().color(foregroundRole()));
}

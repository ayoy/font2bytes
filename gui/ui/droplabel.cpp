#include "droplabel.h"
#include <QPainter>

DropLabel::DropLabel(QWidget *parent):
    PromptLabel(parent)
{
    updateStyleSheet();
}

void DropLabel::updateStyleSheet()
{
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

void DropLabel::setDropActionAvailable(bool available)
{
    if (m_dropActionAvailable != available) {
        m_dropActionAvailable = available;
        updateStyleSheet();
        update();
    }
}

void DropLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int xOffset = 40;
    const int yOffset = 80;
    const qreal cornerRadius = 40.0;

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

#include "promptlabel.h"

PromptLabel::PromptLabel(QWidget *parent):
    QLabel(parent),
    defaultPalette(palette())
{
    defaultPalette.setColor(foregroundRole(), Qt::gray);
    setPalette(defaultPalette);
    setAutoFillBackground(true);

    setFont(QFont("Helvetica", 42, QFont::Black));
}

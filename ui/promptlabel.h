#ifndef PROMPTLABEL_H
#define PROMPTLABEL_H

#include <QLabel>

class PromptLabel : public QLabel
{
public:
    PromptLabel(QWidget * parent = nullptr);

protected:
    QPalette defaultPalette;

};

#endif // PROMPTLABEL_H

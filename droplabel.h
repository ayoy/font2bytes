#ifndef DROPLABEL_H
#define DROPLABEL_H

#include <QLabel>

class DropLabel : public QLabel
{
public:
    explicit DropLabel(QWidget * parent = 0);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // DROPLABEL_H

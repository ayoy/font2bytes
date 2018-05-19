#ifndef DROPLABEL_H
#define DROPLABEL_H

#include "promptlabel.h"
#include <QApplication>

class DropLabel : public PromptLabel
{
    Q_OBJECT
    Q_PROPERTY(bool dropActionAvailable READ isDropActionAvailable WRITE setDropActionAvailable)

public:
    explicit DropLabel(QWidget * parent = nullptr);

    inline bool isDropActionAvailable() const { return m_dropActionAvailable; }

public slots:
    void setDropActionAvailable(bool available);

protected:
    void paintEvent(QPaintEvent *event) override;
    void updateStyleSheet();

private:
    bool m_dropActionAvailable { false };
};

#endif // DROPLABEL_H

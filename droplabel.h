#ifndef DROPLABEL_H
#define DROPLABEL_H

#include <QLabel>
#include <QApplication>

class DropLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(bool dropActionAvailable READ isDropActionAvailable WRITE setDropActionAvailable)

public:
    explicit DropLabel(QWidget * parent = nullptr);

    inline bool isDropActionAvailable() const {
        return m_dropActionAvailable;
    }

public slots:
    inline void setDropActionAvailable(bool available) {
        if (m_dropActionAvailable != available) {
            m_dropActionAvailable = available;
            updateStyleSheet();
            update();
        }
    }

protected:
    void paintEvent(QPaintEvent *event) override;
    void updateStyleSheet();
    bool m_dropActionAvailable;

    QPalette defaultPalette;
};

#endif // DROPLABEL_H

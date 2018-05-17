#ifndef DROPPABLESTACKEDWIDGET_H
#define DROPPABLESTACKEDWIDGET_H

#include <QStackedWidget>

class DroppableStackedWidget : public QStackedWidget
{
    Q_OBJECT
    Q_PROPERTY(bool dropActionAvailable READ isDropActionAvailable WRITE setDropActionAvailable NOTIFY dropActionAvailableChanged)

public:
    explicit DroppableStackedWidget(QWidget * parent = nullptr);

    inline bool isDropActionAvailable() const {
        return m_dropActionAvailable;
    }

signals:
    void dropActionAvailableChanged(bool available);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

    inline void setDropActionAvailable(bool available) {
        if (m_dropActionAvailable != available) {
            m_dropActionAvailable = available;
            emit dropActionAvailableChanged(available);
        }
    }

private:
    bool m_dropActionAvailable = false;
};

#endif // DROPPABLESTACKEDWIDGET_H

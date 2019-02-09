#include "droppablestackedwidget.h"
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>

DroppableStackedWidget::DroppableStackedWidget(QWidget * parent):
    QStackedWidget(parent)
{
}

void DroppableStackedWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->accept();
        setDropActionAvailable(true);
    }
}

void DroppableStackedWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
    setDropActionAvailable(false);
}

void DroppableStackedWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        QUrl url = event->mimeData()->urls().last();
        qDebug() << "Dropped file with url:" << url.path();
        emit imageFileDropped(url);
        setDropActionAvailable(false);
    }
}

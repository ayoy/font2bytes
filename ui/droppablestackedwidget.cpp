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
        qDebug() << __PRETTY_FUNCTION__ << url;
        emit imageFileDropped(url);
        setDropActionAvailable(false);
    }
}

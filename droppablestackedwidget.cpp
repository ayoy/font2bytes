#include "droppablestackedwidget.h"
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QImageReader>

DroppableStackedWidget::DroppableStackedWidget(QWidget * parent):
    QStackedWidget(parent)
{
    setAcceptDrops(true);
}

void DroppableStackedWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        QUrl url = event->mimeData()->urls().last();
        qDebug() << __PRETTY_FUNCTION__ << url;
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
    const QMimeData *mimeData = event->mimeData();
    qDebug() << __PRETTY_FUNCTION__ << mimeData;
    setDropActionAvailable(false);
}

#include "mylistwidget.h"
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

MyListWidget::MyListWidget(QWidget *parent) : QListWidget(parent)
{
    this->setAcceptDrops(true);
}

MyListWidget::~MyListWidget()
{

}

void MyListWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPoint = event->pos();
        m_dragItem = this->itemAt(event->pos());
    }

    QListWidget::mousePressEvent(event);
}

void MyListWidget::mouseMoveEvent(QMouseEvent *event)
{
    //Make sure to hold the left button to move.
    if (event->buttons() & Qt::LeftButton) {
        QPoint temp = event->pos() - m_dragPoint;
        //Only if this length is greater than the default distance will be considered as a drag operation by the system.
        if (temp.manhattanLength() > QApplication::startDragDistance()) {
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;
            mimeData->setText(m_dragItem->text());
            drag->setMimeData(mimeData);
            auto action = drag->exec(Qt::CopyAction | Qt::MoveAction);

            if (action == (Qt::CopyAction) || (action == Qt::MoveAction)) {
                //When successfully dragged, delete the dragged item.
                auto i = this->takeItem(this->row(m_dragItem));
                delete i;
            }
        }
    }
    QListWidget::mouseMoveEvent(event);
}

void MyListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();
}

void MyListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();
}

void MyListWidget::dropEvent(QDropEvent *event)
{
    QString str = event->mimeData()->text();
    if (!str.isEmpty()) {
        //Find the item whose current mouse position is in the widget.
        auto item = this->itemAt(event->pos());
        if (!item)
            this->addItem(str);
        else
            this->insertItem(this->row(item),str);

        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

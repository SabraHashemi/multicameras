#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>

class QMouseEvent;
class QDragEnterEvent;
class QDragMoveEvent;
class QDropEvent;
class QListWidgetItem;

class MyListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit MyListWidget(QWidget *parent = nullptr);

    ~MyListWidget();
    protected:
        // Rewrite the following two functions to complete the drag and drop operation from the widget
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        // Rewrite the following three functions to complete the operation of accepting foreign drag and drop
        void dragEnterEvent(QDragEnterEvent *event);
        void dragMoveEvent(QDragMoveEvent *event);
        void dropEvent(QDropEvent *event);
    private:
        // Record the starting point of the drag and drop
        QPoint m_dragPoint;
        //record dragged item.
        QListWidgetItem *m_dragItem;
};

#endif // MYLISTWIDGET_H

#pragma execution_character_set("utf-8")

#include "camerascene.h"
#include <QGraphicsSceneMouseEvent>
#include <QRubberBand>

#include "mypixmapitem.h"
#include <QDebug>

const QSizeF CameraScene::SIZE(656, 492);
CameraScene::CameraScene(QObject *parent)
//    : QGraphicsScene(parent)
    : QGraphicsScene(QRectF(QPointF(0, 0), SIZE), parent)
{
    setBackgroundBrush(QColor(Qt::white));
    connect(this, &CameraScene::sceneRectChanged, this, &CameraScene::handleSceneRectChanged);

    initItems();

    updateItemPos();
}

CameraScene::~CameraScene()
{
    delete mImageItem;
}

void CameraScene::updateImage(const QImage &image)
{
    if (mImageItem != NULL) {
        QPixmap pix = QPixmap::fromImage(image);
        mImageItem->setPixmap(pix);
    } else {
        // the first time
        insertImage(image);
    }
}

bool CameraScene::getImage(QImage &image)
{
    if (mImageItem != NULL) {
        image = mImageItem->pixmap().toImage();
        return true;
    }
    return false;
}

void CameraScene::updateRect(QRectF rect, const QPointF &pos)
{
    //    mRect.setRect(rect);
    //    mRect.setPen(QPen(Qt::green));
    //    mRect.setPos(pos);

    //    QPointF center = sceneRect().center();

    //    QPointF rectCenter(pos.x() + rect.width()/2, pos.y() + rect.height()/2);

    //    updateXYInfo((rectCenter - center).x(), (rectCenter - center).y());
}
#include <QPainter>
void CameraScene::showGrid(bool flag, double scale)
{
    if (!flag) {
        setForegroundBrush(QColor(Qt::transparent));
//        setBackgroundBrush(QColor(Qt::black));
    } else {
        QPolygonF myPolygon1;
        myPolygon1 << QPointF(0, 50) << QPointF(100, 50);
        QPolygonF myPolygon2;
        myPolygon2 << QPointF(50, 0) << QPointF(50, 100);
        QPixmap pixmap(100, 100);

        pixmap.fill(Qt::transparent);
//        pixmap.fill(Qt::black);
        QPainter painter(&pixmap);

        QVector<qreal> dashes; //line style
        qreal space = 2;
        dashes << 2 << space << 2 <<space;
        QPen pen(Qt::lightGray,1);
        pen.setDashPattern(dashes);
        pen.setWidth(1);

        painter.setPen(pen);
        painter.translate(0, 0);
        painter.setBackground(QColor(Qt::black));
        painter.drawPolyline(myPolygon1);
        painter.drawPolyline(myPolygon2);
        // Set to foreground, above the image display
        setForegroundBrush(pixmap);
//        setBackgroundBrush(pixmap);
    }
}

void CameraScene::showCameraOnly()
{
    // Some accessibility features for displaying pictures
    if (mImageItem != NULL) {
        mImageItem->setVisible(true);
    }
    //    mSLine.setVisible(true);
    //    mTLine.setVisible(true);
    //    mS.setVisible(true);
    //    mT.setVisible(true);
    //    mXInfo.setVisible(true);
    //    mYInfo.setVisible(true);
    mRect.setVisible(true);
}

void CameraScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF scenePos = event->scenePos();
    QPoint pos = scenePos.toPoint();
    QRgb rgb = 0;
    if (mImageItem != NULL) {
        QImage image = mImageItem->pixmap().toImage();
        if (pos.x() >= 0 && pos.x() <= image.width() && pos.y() >= 0 && pos.y() <= image.height()) {
            rgb = image.pixel(pos);
        }

    }

    emit sigImageInfo(pos, rgb);
}

void CameraScene::handleSceneRectChanged(const QRectF &rect)
{
    updateItemPos();
}

void CameraScene::insertImage(const QImage &image)
{
    QPixmap pix = QPixmap::fromImage(image);
    mImageItem = new MyPixmapItem(pix);
    addItem(mImageItem);
    mImageItem->setPos(0, 0);
    // Align the area of the view with the area of the image so that the center of the view is the center of the image
    setSceneRect(0, 0, image.width(), image.height());
}

void CameraScene::initItems()
{
    //    mSLine.setZValue(100);
    //    mSLine.setPen(QPen(Qt::blue, 0));
    //    mTLine.setZValue(100);
    //    mTLine.setPen(QPen(Qt::blue, 0));
    //    addItem(&mSLine);
    //    addItem(&mTLine);

    //    mS.setZValue(100);
    //    mS.setHtml("<font color='blue' size='16'>S</font>");
    //    mT.setZValue(100);
    //    mT.setHtml("<font color='blue' size='16'>T</font>");
    //    addItem(&mS);
    //    addItem(&mT);

    //    mXInfo.setZValue(100);
    //    addItem(&mXInfo);

    //    mYInfo.setZValue(100);
    //    addItem(&mYInfo);

    mRect.setZValue(100);
    addItem(&mRect);
}

void CameraScene::updateItemPos()
{
    QPointF topLeft = sceneRect().topLeft();
    QPointF topRight = sceneRect().topRight();
    QPointF bottomLeft = sceneRect().bottomLeft();
    QPointF bottomRight = sceneRect().bottomRight();

    //    mTLine.setLine(QLineF((topLeft + bottomLeft) * 0.5, (topRight + bottomRight) * 0.5));
    //    mSLine.setLine(QLineF((topLeft + topRight) * 0.5, (bottomLeft + bottomRight) * 0.5));
    //    mS.setPos((topLeft + topRight) * 0.5);
    //    mT.setPos((topLeft + bottomLeft) * 0.5);

    //    mXInfo.setPos(topRight - QPointF(200, -10));
    //    mYInfo.setPos(topRight - QPointF(200, -40));

    updateRect(QRectF(0, 0, 100, 100), sceneRect().center() - QPointF(50, 50));
}

void CameraScene::updateXYInfo(qreal x, qreal y)
{
    //    mXInfo.setHtml(QString("<font color='yellow' size='16'>x = %1</font>").arg(x));
    //    mYInfo.setHtml(QString("<font color='yellow' size='16'>y = %1</font>").arg(y));
}



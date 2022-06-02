#ifndef CAMERASCENE_H
#define CAMERASCENE_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QColor;
class QRubberBand;
class MyPixmapItem;

QT_END_NAMESPACE

class CameraScene : public QGraphicsScene
{
    Q_OBJECT

public:
    CameraScene(QObject *parent = 0);

    ~CameraScene();
    /**
     * @brief Update the displayed image
     * @param image
     */
    void updateImage(const QImage &image);

    /**
     * @brief currently displayed image
     * @param image
     * @return
     */
    bool getImage(QImage &image);
    /**
     * @brief Update the size and position of the rectangle
     * @param rect
     * @param pos
     */
    void updateRect(QRectF rect, const QPointF &pos);

    /**
     * @brief show grid
     * @param flag
     */
    void showGrid(bool flag, double scale);

    /**
     * @brief show only images
     */
    void showCameraOnly();
protected:
    /**
     * @brief Mouse movement event, mainly used to display the pixel of the image corresponding to the current position of the mouse
     * @param event
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private slots:

    void handleSceneRectChanged(const QRectF &rect);
signals:
    void sigImageInfo(QPoint point, QRgb rgb);
private:
    void insertImage(const QImage &image);
    /**
     * @brief Initialize all items in the interface
     */
    void initItems();
    /**
     * @brief When the size of the interface changes, update the position of each item
     */
    void updateItemPos();
    /**
     * @brief Update the deviation of the rectangle box from the center of the scene
     * @param x
     * @param y
     */
    void updateXYInfo(qreal x, qreal y);
private:
    const static QSizeF SIZE;
    // collected images
    MyPixmapItem *mImageItem = NULL;
    // two center lines
    QGraphicsLineItem mTLine;
    QGraphicsLineItem mSLine;
    // Text showing centerline
    QGraphicsTextItem mS;
    QGraphicsTextItem mT;
    // Display the eccentric distance of the picture
    QGraphicsTextItem mXInfo;
    QGraphicsTextItem mYInfo;
    // Rectangle
    QGraphicsRectItem mRect;
};

#endif // CAMERASCENE_H

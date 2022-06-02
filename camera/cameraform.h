#ifndef CAMERAFORM_H
#define CAMERAFORM_H

#include "camera/camerascene.h"
#include "mycamera.h"
#include "opencv2/opencv.hpp"
#include <QContextMenuEvent>
#include <QGraphicsView>
#include <QMenu>
#include <QWidget>

namespace Ui {
class CameraForm;
}

class CameraForm : public QWidget
{
    Q_OBJECT

public:
    explicit CameraForm(QWidget *parent = 0);
    ~CameraForm();

    void contextMenuEvent(QContextMenuEvent *event) override;

    /**
     * @brief the name of the camera
     * @return
     */
    QString cameraName() const;

    void setCameraName(const QString &cameraName);

    /**
     * @brief Turn on the camera
     * @param cameraName
     * @return
     */
    bool openCamera(const QString &cameraName);

    /**
     * @brief turn off the camera
     */
    void closeCamera();

    /**
     * @brief take a picture
     * @param position
     */
    void grabOneImage();

    /**
     * @brief Continuously take pictures, used to adjust the camera position in the early stage
     */
    void grabContinous();

    /**
     * @brief Stop taking pictures
     */
    void grabStop();

public slots:
    /**
     * @brief Update the image captured by the display camera
     * @param image
     */
    void updateCameraImage(cv::Mat image);

    /**
     * @brief Update the view and the corresponding rectangle
     * @param image image
     * @param width rectangle width
     * @param height rectangle height
     * @param x upper left corner of rectangle
     * @param y upper right corner of rectangle
     */
    void updateROI(cv::Mat image, double width, double height, double x, double y);

    /**
     * @brief enlarge
     */
    void zoomIn();

    /**
     * @brief zoom out
     */
    void zoomOut();

    /**
     * @brief Fit to view size
     */
    void fit();

    /**
     * @brief restore view size
     */
    void resetScale();

    /**
     * @brief zoom of the view
     * @param scale
     */
    void changeSceneScale(const double &scale);

    /***Right-click menu bar features*****/
    void showCamera();

    void saveImage();

    void showGrid(bool checked = false);
    /***Right-click menu bar features*****/
signals:
    void sigImageInfo(QPoint point, QRgb rgb);
private:
    void initMenu();

private:
    Ui::CameraForm *ui;
    QMenu *mMenu = NULL;
    CameraScene *mScene = NULL;
    QGraphicsView *mView = NULL;

    int mCameraId = 0;
    QString mCameraName;

    // Camera (On/Off/Single/Burst/Pause)
    MyCamera *mCamera;

    // zoom scale
    double mScale = 1;
};

#endif // CAMERAFORM_H

#ifndef CameraPanel_H
#define CameraPanel_H

#include "camera/cameraform.h"
#include "cameramanager.h"
#include "cameraparameters.h"
#include "scandevices.h"
#include <QDockWidget>
#include <QMainWindow>
#include <QMdiArea>

namespace Ui {
class CameraPanel;
}

class CameraPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit CameraPanel(QWidget *parent = 0);
    ~CameraPanel();
private slots:
    /**
     * @brief Initialize, update menu bar
     */
    void updateMenus();

    /**
     * @brief save Picture
     */
    void saveImage();

    /**
     * @brief Turn on the camera
     */
    void openCamera();

    /**
     * @brief turn off the camera
     */
    void closeCamera();

    /**
     * @brief take a picture
     */
    void grabOne();

    /**
     * @brief Continuous acquisition of pictures
     */
    void grabContinous();

    /**
     * @brief Stop taking pictures
     */
    void grabStop();

    /**
     * @brief Zoom out
     */
    void zoomIn();

    /**
     * @brief Zoom in view
     */
    void zoomOut();

    /**
     * @brief adaptive
     */
    void zoomFit();

    /**
     * @brief show grid
     * @param checked
     */
    void showGrid(bool checked = false);

    void updateCurrentCamera(QString cameraName);

    void handleImageInfo(QPoint point, QRgb rgb);
private:
    void createActionConnections();

    void createDocks();

    /**
     * @brief Find whether the corresponding child window is already open
     * @param camera name
     * @return
     */
    QMdiSubWindow *findMdiChild(const QString &cameraName) const;

    /**
     * @brief the currently active child window
     * @return
     */
    CameraForm *activeMdiChild() const;
private:
    Ui::CameraPanel *ui;

    QString mCurrentCamera;
    // Device List
    QDockWidget *mCameraListWidget;
    // Device list interface
    ScanDevices *mScanDevices;
    // camera properties
    QDockWidget *mCameraParamsWidget;
    // Interface for camera properties
    CameraParameters *mCameraParameters;
};

#endif // CameraPanel_H

#ifndef MYCAMERA_H
#define MYCAMERA_H

#include "baslerSDK/include/HardwareTriggerConfiguration.h"
#include "opencv2/opencv.hpp"
#include <pylon/PylonIncludes.h>
#include <pylon/gige/PylonGigEIncludes.h>
#include <QObject>

// Settings to use Basler GigE cameras.
using namespace Basler_GigECameraParams;
// Namespace for using pylon objects.
using namespace Pylon;
// Namespace for using cout.
using namespace std;

using namespace GenApi;

class CameraManager;

class MyCamera : public QObject,
        public Pylon::CImageEventHandler             // Allows you to get informed about received images and grab errors.
{
    Q_OBJECT
public:
    explicit MyCamera(QObject *parent = nullptr);
    ~MyCamera();

    /**
     * @brief Turn on the camera
     * @param cameraFN
     * @return
     */
    bool openCamera(const QString &cameraFN);

    /**
     * @brief turn off the camera
     */
    void closeCamera();

    /**
     * @brief Asynchronous callback for acquired image
     * @param camera
     * @param grabResult
     */
    void OnImageGrabbed(Pylon::CInstantCamera& camera, const Pylon::CGrabResultPtr& grabResult) override;

public slots:
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
signals:
    /**
     * @brief get new image
     * @param image 
     * @param position where the image was taken
     */
    void sigGrabNewImage(cv::Mat image);
private:
    // single shot
    CAcquireSingleFrameConfiguration mSingleConfiguration;
    // continuous shooting
    CAcquireContinuousConfiguration mContinousConfiguration;
    // hardware trigger
    CHardwareTriggerConfiguration mHardwareTriggerConfig;
    // currently operating camera
    CBaslerGigEInstantCamera *mCamera = NULL;
    // the name of the camera
    QString mCameraName;
    // the name of the camera
    CameraManager *mCameraManager;
};

#endif // MYCAMERA_H

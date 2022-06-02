#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "opencv2/opencv.hpp"
#include <pylon/PylonIncludes.h>
#include <pylon/gige/PylonGigEIncludes.h>
#include <QMap>
#include <QObject>

#define QT_THREAD_SUPPORT
#include <qmutex.h>

// Settings to use Basler GigE cameras.
using namespace Basler_GigECameraParams;
// Namespace for using pylon objects.
using namespace Pylon;
// Namespace for using cout.
using namespace std;

using namespace GenApi;


class CameraManager : public QObject,
        public Pylon::CImageEventHandler,             // Allows you to get informed about received images and grab errors.
        public Pylon::CConfigurationEventHandler     // Allows you to get informed about device removal.
{
    Q_OBJECT
private:
    static CameraManager *mInstance;
    explicit CameraManager(QObject *parent = nullptr);

public:
    static CameraManager *getInstance(){
        return mInstance;
    }

    ~CameraManager();
public:
    /**
     * @brief Search all connected cameras
     * @return
     */
    int searchCameras();

    /**
     * @brief Open the corresponding Camera
     * @param cameraFriendlyName
     * @return Error code 0: success -1: failure
     */
    bool openCamera(QString &cameraFN);

    /**
     * @brief load configuration file
     * @param cameraFN
     * @param fileName
     */
    void load(QString &cameraFN, QString &fileName);

    /**
     * @brief save configuration file
     * @param cameraFN
     */
    void save(QString &cameraFN);

    /**
     * @brief Close Camera
     * @param cameraFN
     */
    void closeCamera(QString &cameraFN);

    /**
     * @brief Capture one image at a time
     */
    void grabOne(QString &cameraFN);

    /**
     * @brief Continuous acquisition of pictures
     */
    void grabContinuous(QString &cameraFN);

    /**
     * @brief Stop capturing images
     * @param cameraFN
     */
    void stopGrab(QString &cameraFN);

    /**
     * @brief set frame rate
     * @param name
     * @param value
     */
    void setAcquisitionFrameRate(QString &name, double value);

    /**
     * @brief get frame rate
     * @param name
     * @param minValue
     * @param value
     * @param maxValue
     * @param inc
     */
    void getAcquisitionFrameRate(QString &name, double &minValue, double &value, double &maxValue, double &inc);

    /**
     * @brief Set exposure time
     * @param time
     */
    void setExposureTime(QString &name, qint64 time);

    /**
     * @brief Get exposure time
     * @param name
     * @param minValue
     * @param value
     * @param maxValue
     * @param inc
     */
    void getExposureTime(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc);

    /**
     * @brief set gain
     * @param value
     */
    void setGain(QString &name, qint64 value);

    void getGain(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc);

    void setAOI(QString &name, qint64 width, qint64 height, qint64 offsetX, qint64 offsetY);

    void setPixelFormat(QString &name, const QString &format = QString());

    void setWidth(QString &name, qint64 value);

    void getWidth(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc);

    void setHeight(QString &name, qint64 value);

    void getHeight(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc);

    void setoffsetX(QString &name, qint64 value);

    void getoffsetX(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc);

    void setoffsetY(QString &name, qint64 value);

    void getoffsetY(QString &name, qint64 &minValue, qint64 &value, qint64 &maxValue, qint64 &inc);

    bool isOpened(QString &name);

    void addOpenCamera(const QString& name, CBaslerGigEInstantCamera* camera);

    void removeOpenCamera(const QString& name);

    // Pylon::CImageEventHandler functions
    virtual void OnImagesSkipped(Pylon::CInstantCamera& camera, size_t countOfSkippedImages) override;
    virtual void OnImageGrabbed(Pylon::CInstantCamera& camera, const Pylon::CGrabResultPtr& grabResult) override;

    // Pylon::CConfigurationEventHandler functions
    virtual void OnAttach(Pylon::CInstantCamera& camera) override;
    virtual void OnAttached(Pylon::CInstantCamera& camera) override;
    virtual void OnDetach(Pylon::CInstantCamera& camera) override;
    virtual void OnDetached(Pylon::CInstantCamera& camera) override;
    virtual void OnDestroy(Pylon::CInstantCamera& camera) override;
    virtual void OnDestroyed(Pylon::CInstantCamera& camera) override;
    virtual void OnOpen(Pylon::CInstantCamera& camera) override;
    virtual void OnOpened(Pylon::CInstantCamera& camera) override;
    virtual void OnClose(Pylon::CInstantCamera& camera) override;
    virtual void OnClosed(Pylon::CInstantCamera& camera) override;
    virtual void OnGrabStart(Pylon::CInstantCamera& camera) override;
    virtual void OnGrabStarted(Pylon::CInstantCamera& camera) override;
    virtual void OnGrabStop(Pylon::CInstantCamera& camera) override;
    virtual void OnGrabStopped(Pylon::CInstantCamera& camera) override;
    virtual void OnGrabError(Pylon::CInstantCamera& camera, const char* errorMessage) override;
    virtual void OnCameraDeviceRemoved(Pylon::CInstantCamera& camera) override;

signals:
    void sigCameraUpdate(const QStringList &list);

    void sigupdateImage(cv::Mat image);

public slots:


private:
    bool registerHandler(CInstantCamera *camera);
    /**
     * @brief Adjust value to make it comply with range and increment passed
     * @param val
     * @param minimum
     * @param maximum
     * @param inc
     * @return
     */
    qint64 adjust(qint64 val, qint64 minimum, qint64 maximum, qint64 inc);

private:
    // How many cameras can be connected
    const static int mMaxCamerasToUse = 3;

    QMutex mutex;

    // The grab result retrieved from the camera
    CGrabResultPtr mGrabResult;
    // single shot
    CAcquireSingleFrameConfiguration mSingleConfiguration;
    // continuous shooting
    CAcquireContinuousConfiguration mContinousConfiguration;
    // software trigger
    CSoftwareTriggerConfiguration mSoftwareTriggerConfig;
    // All Ethernet connected cameras
    //    CBaslerGigEInstantCameraArray mGigECameras;
    // currently operating camera
    CBaslerGigEInstantCamera *mCurrentCamera = NULL;
    // Searched camera list
    // List of all attached devices
    Pylon::DeviceInfoList_t mCamerasInfo;
    QStringList mCameraList;
    // open camera cache
    QMap<QString, CBaslerGigEInstantCamera*> mOpenedCameras;
};

#endif // CAMERAMANAGER_H

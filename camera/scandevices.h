#ifndef ScanDevices_H
#define ScanDevices_H

#include <QWidget>
#include <QListWidgetItem>
#include "cameramanager.h"

namespace Ui {
class ScanDevices;
}

class ScanDevices : public QWidget
{
    Q_OBJECT

public:
    explicit ScanDevices(QWidget *parent = 0);
    ~ScanDevices();

private slots:
    void on_btn_search_clicked();

    void handleCameraUpdate(const QStringList &list);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

signals:
    void sigActivated(QString cameraName);

private:
    Ui::ScanDevices *ui;
    CameraManager *mCameras = NULL;
};

#endif // ScanDevices_H

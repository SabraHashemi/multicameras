#pragma execution_character_set("utf-8")
#include "scandevices.h"
#include "ui_scandevices.h"
#include <QDebug>

ScanDevices::ScanDevices(QWidget *parent)
    : QWidget(parent), ui(new Ui::ScanDevices), mCameras(CameraManager::getInstance())
{
    ui->setupUi(this);
    connect(mCameras, &CameraManager::sigCameraUpdate, this, &ScanDevices::handleCameraUpdate);
}

ScanDevices::~ScanDevices()
{
    qDebug() << "~ScanDevices";
    delete mCameras;
    delete ui;
}

void ScanDevices::on_btn_search_clicked()
{
    mCameras->searchCameras();
}

void ScanDevices::handleCameraUpdate(const QStringList &list)
{
    ui->listWidget->clear();
    ui->listWidget->addItems(list);
}

void ScanDevices::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug() << "itemDoubleClicked" << item->text();
    QString friendName = item->text();

    //mCameras->openCamera(friendName);
}

void ScanDevices::on_listWidget_itemClicked(QListWidgetItem *item)
{
    qDebug() << "itemClicked" << item->text();
    emit sigActivated(item->text());
}


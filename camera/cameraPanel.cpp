#pragma execution_character_set("utf-8")

#include "cameraPanel.h"
#include "ui_CameraPanel.h"
#include <QDebug>
#include <QMdiSubWindow>
#include <QMessageBox>

CameraPanel::CameraPanel(QWidget *parent) : QMainWindow(parent), ui(new Ui::CameraPanel)
{
    ui->setupUi(this);
    // When the child window is switched, to update the menu bar
    connect(ui->mdiArea, &QMdiArea::subWindowActivated, this, &CameraPanel::updateMenus);
    createDocks();
    createActionConnections();

    updateMenus();
}

CameraPanel::~CameraPanel()
{
    delete ui;
}

void CameraPanel::updateMenus()
{
     qDebug() << "updateMenus";
     bool hasMdiChild = (activeMdiChild() != 0);
     ui->action_Save->setEnabled(hasMdiChild);
     ui->action_ZoomIn->setEnabled(hasMdiChild);
     ui->action_ZoomOut->setEnabled(hasMdiChild);
     ui->action_ZoomFit->setEnabled(hasMdiChild);
     ui->action_ShowGrid->setEnabled(hasMdiChild);
     ui->action_tile->setEnabled(hasMdiChild);
     ui->action_cascade->setEnabled(hasMdiChild);
}

void CameraPanel::saveImage()
{
    CameraForm *mdiChild = activeMdiChild();
    mdiChild->saveImage();
}

void CameraPanel::openCamera()
{
    // 打开相机
    qDebug() << "openCamera" << mCurrentCamera;
    CameraForm* child = new CameraForm;
    child->setCameraName(mCurrentCamera);
    bool res = child->openCamera(mCurrentCamera);

    if (res) {
        qDebug() << "openCamera" << mCurrentCamera;
        ui->mdiArea->addSubWindow(child)->showMaximized();
        connect(child, &CameraForm::sigImageInfo, this, &CameraPanel::handleImageInfo);
        ui->action_Open->setEnabled(false);
        ui->action_Close->setEnabled(true);
        ui->action_Single->setEnabled(true);
        ui->action_Contious->setEnabled(true);
        ui->action_Stop->setEnabled(true);

        mCameraParameters->updateCamera(mCurrentCamera);
    } else {
        delete child;
        QMessageBox::information(this, "warning", "Failed to open");
    }
}

void CameraPanel::closeCamera()
{
    if (QMdiSubWindow *existing = findMdiChild(mCurrentCamera)) {
        ui->mdiArea->setActiveSubWindow(existing);
        // current window camera to capture images
        CameraForm *mdiChild = qobject_cast<CameraForm *>(existing->widget());
        disconnect(mdiChild, &CameraForm::sigImageInfo, this, &CameraPanel::handleImageInfo);
        mdiChild->closeCamera();
        ui->mdiArea->removeSubWindow(mdiChild);
        mdiChild->close();

        ui->action_Open->setEnabled(true);
        ui->action_Close->setEnabled(false);
        ui->action_Single->setEnabled(false);
        ui->action_Contious->setEnabled(false);
        ui->action_Stop->setEnabled(false);
        mCameraParameters->updateCamera(mCurrentCamera);
    }
}

void CameraPanel::grabOne()
{
    // Load the display interface
    if (QMdiSubWindow *existing = findMdiChild(mCurrentCamera)) {
        ui->mdiArea->setActiveSubWindow(existing);
        // current window camera to capture images
        CameraForm *mdiChild = qobject_cast<CameraForm *>(existing->widget());
        mdiChild->grabOneImage();
    }
}

void CameraPanel::grabContinous()
{
    // Load the display interface
    if (QMdiSubWindow *existing = findMdiChild(mCurrentCamera)) {
        ui->mdiArea->setActiveSubWindow(existing);
        // current window camera to capture images
        CameraForm *mdiChild = qobject_cast<CameraForm *>(existing->widget());
        mdiChild->grabContinous();
    }
}

void CameraPanel::grabStop()
{
    if (QMdiSubWindow *existing = findMdiChild(mCurrentCamera)) {
        ui->mdiArea->setActiveSubWindow(existing);
        // current window camera to capture images
        CameraForm *mdiChild = qobject_cast<CameraForm *>(existing->widget());
        mdiChild->grabStop();
    }
}

void CameraPanel::zoomIn()
{
    CameraForm* form = activeMdiChild();
    if (form != NULL) {
        form->zoomIn();
    }
}

void CameraPanel::zoomOut()
{
    CameraForm* form = activeMdiChild();

    if (form != NULL) {
        form->zoomOut();
    }
}

void CameraPanel::zoomFit()
{
    CameraForm* form = activeMdiChild();

    if (form != NULL) {
        form->fit();
    }
}

void CameraPanel::showGrid(bool checked)
{
    CameraForm* form = activeMdiChild();

    if (form != NULL) {
        form->showGrid(checked);
    }
}

void CameraPanel::updateCurrentCamera(QString cameraName)
{
    mCurrentCamera = cameraName;

    if (findMdiChild(mCurrentCamera)) {
        ui->action_Open->setEnabled(false);
        ui->action_Close->setEnabled(true);
        ui->action_Single->setEnabled(true);
        ui->action_Contious->setEnabled(true);
        ui->action_Stop->setEnabled(true);
    } else {
        ui->action_Open->setEnabled(true);
        ui->action_Close->setEnabled(false);
        ui->action_Single->setEnabled(false);
        ui->action_Contious->setEnabled(false);
        ui->action_Stop->setEnabled(false);
    }
}

void CameraPanel::handleImageInfo(QPoint point, QRgb rgb)
{
    if (point.x() == -1 || point.y() == -1) {
        // 鼠标移出窗口
        ui->statusbar->showMessage("");
    } else {
        // 鼠标在窗口中的位置
        ui->statusbar->showMessage(QString("(%1, %2)  (R:%3, G:%4, B:%5)")
                                   .arg(point.x())
                                   .arg(point.y())
                                   .arg(qRed(rgb))
                                   .arg(qGreen(rgb))
                                   .arg(qBlue(rgb)));
    }

}

void CameraPanel::createActionConnections()
{
    connect(ui->action_Save, &QAction::triggered, this, &CameraPanel::saveImage);

    connect(ui->action_Exit, &QAction::triggered, this, &CameraPanel::close);

    connect(ui->action_Open, &QAction::triggered, this, &CameraPanel::openCamera);

    connect(ui->action_Close, &QAction::triggered, this, &CameraPanel::closeCamera);

    connect(ui->action_Single, &QAction::triggered, this, &CameraPanel::grabOne);

    connect(ui->action_Contious, &QAction::triggered, this, &CameraPanel::grabContinous);

    connect(ui->action_Stop, &QAction::triggered, this, &CameraPanel::grabStop);

    connect(ui->action_ZoomIn, &QAction::triggered, this, &CameraPanel::zoomIn);

    connect(ui->action_ZoomOut, &QAction::triggered, this, &CameraPanel::zoomOut);

    connect(ui->action_ZoomFit, &QAction::triggered, this, &CameraPanel::zoomFit);

    ui->action_ShowGrid->setCheckable(true);
    connect(ui->action_ShowGrid, &QAction::triggered, this, &CameraPanel::showGrid);

    ui->action_Open->setEnabled(false);
    ui->action_Close->setEnabled(false);
    ui->action_Single->setEnabled(false);
    ui->action_Contious->setEnabled(false);
    ui->action_Stop->setEnabled(false);

    connect(ui->action_Device, &QAction::triggered, [this](bool checked){
        if (checked) {
            mCameraListWidget->show();
        } else {mCameraListWidget->hide();}});
    connect(ui->action_Params, &QAction::triggered, [this](bool checked){
        if (checked) {
            mCameraParamsWidget->show();
        } else {mCameraParamsWidget->hide();}});

    connect(ui->action_tile, &QAction::triggered, ui->mdiArea, &QMdiArea::tileSubWindows);
    connect(ui->action_cascade, &QAction::triggered, ui->mdiArea, &QMdiArea::cascadeSubWindows);
}

void CameraPanel::createDocks()
{
    // Device List
    mCameraListWidget = new QDockWidget(this);
    mCameraListWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    mScanDevices = new ScanDevices;
    mCameraListWidget->setWidget(mScanDevices);
    mCameraListWidget->setWindowTitle("Scan");
    addDockWidget(Qt::LeftDockWidgetArea, mCameraListWidget);
    //    mCameraListWidget->setVisible(false);
    // which camera is currently clicked
    connect(mScanDevices, &ScanDevices::sigActivated, this, &CameraPanel::updateCurrentCamera);
    // parameter list
    mCameraParamsWidget = new QDockWidget(this);
    mCameraParamsWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    mCameraParameters = new CameraParameters;
    mCameraParamsWidget->setWidget(mCameraParameters);
    mCameraParamsWidget->setWindowTitle("Properties");
    addDockWidget(Qt::LeftDockWidgetArea, mCameraParamsWidget);
//    mCameraParamsWidget->setVisible(false);
    connect(mScanDevices,
            &ScanDevices::sigActivated,
            mCameraParameters,
            &CameraParameters::updateCamera);
}

QMdiSubWindow *CameraPanel::findMdiChild(const QString &cameraName) const
{
    qDebug() << ui->mdiArea->subWindowList().size();

    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList()) {
        CameraForm *mdiChild = qobject_cast<CameraForm *>(window->widget());
        if (mdiChild != NULL && mdiChild->cameraName() == cameraName)
            return window;
    }
    return 0;
}

CameraForm *CameraPanel::activeMdiChild() const
{
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
        return qobject_cast<CameraForm *>(activeSubWindow->widget());
    return 0;
}

#pragma execution_character_set("utf-8")

#include "cameraform.h"
#include "ui_cameraform.h"
#include <QDebug>
#include <QFileDialog>

CameraForm::CameraForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraForm),
    mScene(new CameraScene),
    mView(new QGraphicsView(mScene)),
    mCamera(new MyCamera)
{
    ui->setupUi(this);
    initMenu();

    ui->widget->layout()->addWidget(mView);
    // The status bar displays the coordinates of the mouse and the color of the pixel it is on
    qRegisterMetaType<cv::Mat>("cv::Mat");
    connect(mScene, &CameraScene::sigImageInfo, this, &CameraForm::sigImageInfo);
    // Camera capture and display
    connect(mCamera, &MyCamera::sigGrabNewImage, this, &CameraForm::updateCameraImage);
}

CameraForm::~CameraForm()
{
    delete ui;
    delete mMenu;
    delete mView;
    delete mScene;

    closeCamera();
}

void CameraForm::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
    //Displays the right mouse button menu at the location where the mouse was clicked
    mMenu->exec(QCursor::pos());
}

void CameraForm::updateCameraImage(cv::Mat image)
{
//    QImage img((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);
    QImage img((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_Indexed8);
    mScene->updateImage(img);
}

void CameraForm::updateROI(cv::Mat image, double width, double height, double x, double y)
{
//    QImage img((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_RGB888);
    QImage img((const unsigned char*)(image.data), image.cols, image.rows, QImage::Format_Indexed8);
    mScene->updateImage(img);
    mScene->updateRect(QRectF(0, 0, width, height), QPointF(x, y));
}

void CameraForm::zoomIn()
{
    changeSceneScale(mScale*1.2);
}

void CameraForm::zoomOut()
{
    changeSceneScale(mScale*0.83);
}

void CameraForm::fit()
{
    mView->fitInView(mScene->sceneRect(), Qt::KeepAspectRatio);
    QMatrix matrix = mView->matrix();
    mScale = matrix.m11();
}

void CameraForm::resetScale()
{
    changeSceneScale(1);
}

void CameraForm::changeSceneScale(const double &scale)
{
    mScale = scale;
    QMatrix matrix;
    matrix.scale(scale, scale);

    mView->setMatrix(matrix);
}

void CameraForm::showCamera()
{
    qDebug() << "showCamera";
    //    updateCameraImage(QImage(QString("D:\\TestResult\\201811\\0\\1.bmp")));
    mScene->showCameraOnly();
}

void CameraForm::saveImage()
{
    QImage image;
    bool res = mScene->getImage(image);
    if (res) {
        QString filePath = QFileDialog::getSaveFileName(this, "Save As", "", tr("Images (*.bmp *.png *.jpg)"));
        image.save(filePath);
    }
}


void CameraForm::showGrid(bool checked)
{
    mScene->showGrid(checked, mScale);
}

void CameraForm::initMenu()
{
    // Initialize right-click menu
    mMenu = new QMenu(this);
    QAction *camera = new QAction(QIcon(""), tr("display image"), mMenu);

    QAction *saveImage = new QAction(QIcon(""), tr("save picture"), mMenu);

    QAction *showGrid = new QAction(QIcon(""), tr("show grid"), mMenu);
    showGrid->setCheckable(true);

    QAction *zoomIn = new QAction(QIcon(""), tr("zoom in"), mMenu);
    QAction *zoomOut = new QAction(QIcon(""), tr("zoom out"), mMenu);
    QAction *fit = new QAction(QIcon(""), tr("fit"), mMenu);
    QAction *reset = new QAction(QIcon(""), tr("reset"), mMenu);

    mMenu->addAction(camera);

    mMenu->addSeparator();

    mMenu->addAction(saveImage);
    mMenu->addSeparator();

    mMenu->addAction(zoomIn);
    mMenu->addAction(zoomOut);
    mMenu->addAction(fit);
    mMenu->addAction(reset);
    mMenu->addSeparator();

    mMenu->addAction(showGrid);

    connect(camera, &QAction::triggered, this, &CameraForm::showCamera);

    connect(saveImage, &QAction::triggered, this, &CameraForm::saveImage);

    connect(zoomIn, &QAction::triggered, this, &CameraForm::zoomIn);
    connect(zoomOut, &QAction::triggered, this, &CameraForm::zoomOut);
    connect(fit, &QAction::triggered, this, &CameraForm::fit);
    connect(reset, &QAction::triggered, this, &CameraForm::resetScale);
    connect(showGrid, &QAction::triggered, this, &CameraForm::showGrid);

}

QString CameraForm::cameraName() const
{
    return mCameraName;
}

void CameraForm::setCameraName(const QString &cameraName)
{
    mCameraName = cameraName;
    setWindowTitle(cameraName);
}

bool CameraForm::openCamera(const QString &cameraName)
{
    return mCamera->openCamera(cameraName);
}

void CameraForm::closeCamera()
{
    mCamera->closeCamera();
}

void CameraForm::grabOneImage()
{
    mCamera->grabOneImage();
}

void CameraForm::grabContinous()
{
    mCamera->grabContinous();
}

void CameraForm::grabStop()
{
    mCamera->grabStop();
}

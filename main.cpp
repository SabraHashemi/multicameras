#include "camera/cameraPanel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CameraPanel w;
    w.show();

    return a.exec();
}

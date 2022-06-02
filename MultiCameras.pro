#-------------------------------------------------
#
# Project
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = baslerSDK
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    camera/cameraform.cpp \
    camera/cameramanager.cpp \
    camera/camerapanel.cpp \
    camera/cameraparameters.cpp \
    camera/camerascene.cpp \
    camera/mycamera.cpp \
    camera/mylistwidget.cpp \
    camera/mypixmapitem.cpp \
    camera/scandevices.cpp \
    camera/scandevices.cpp \
        main.cpp \


HEADERS += \
    camera/cameraform.h \
    camera/cameramanager.h \
    camera/camerapanel.h \
    camera/cameraparameters.h \
    camera/camerascene.h \
    camera/mycamera.h \
    camera/mylistwidget.h \
    camera/mypixmapitem.h \
    camera/scandevices.h \
    camera/scandevices.h \


FORMS += \
    camera/cameraform.ui \
    camera/camerapanel.ui \
    camera/cameraparameters.ui \
    camera/scandevices.ui \
    camera/scandevices.ui \


##Basler相机
#win32: LIBS += -L$$PWD/baslerSDK/pylon/lib/x64/ -lGCBase_MD_VC141_v3_1_Basler_pylon_v5_1
#win32: LIBS += -L$$PWD/baslerSDK/pylon/lib/x64/ -lGenApi_MD_VC141_v3_1_Basler_pylon_v5_1
#win32: LIBS += -L$$PWD/baslerSDK/pylon/lib/x64/ -lPylonBase_v5_1
#win32: LIBS += -L$$PWD/baslerSDK/pylon/lib/x64/ -lPylonC
#win32: LIBS += -L$$PWD/baslerSDK/pylon/lib/x64/ -lPylonGUI_v5_1
#win32: LIBS += -L$$PWD/baslerSDK/pylon/lib/x64/ -lPylonUtility_v5_1

#INCLUDEPATH += $$PWD/baslerSDK/pylon/include

## OpenCV库文件
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/opencv/build/x64/vc15/lib/ -lopencv_world341
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/opencv/build/x64/vc15/lib/ -lopencv_world341d

#INCLUDEPATH += $$PWD/opencv/build/x64/vc14
#DEPENDPATH += $$PWD/opencv/build/x64/vc14
#INCLUDEPATH += $$PWD/opencv/build/include


INCLUDEPATH += D:\\opencv-4.2.0\\opencv-4.2.0\\CudaBuild\\install\\include
INCLUDEPATH += D:\\opencv-4.2.0\\opencv-4.2.0\\CudaBuild\\install\\include\\opencv2
DEPENDPATH += D:\\opencv-4.2.0\\opencv-4.2.0\\CudaBuild\\install\\include


#INCLUDEPATH += C:\Users\ZahRa\AppData\Roaming\Python\Python37\site-packages\numpy\core\include


LIBS += D:\\opencv-4.2.0\\opencv-4.2.0\\CudaBuild\\install\\x64\\vc16\\lib\\opencv_world420.lib


LIBS += D:\\opencv-4.2.0\\opencv-4.2.0\\CudaBuild\\install\\x64\\vc16\\lib\\opencv_world420.lib
LIBS += D:\\opencv-4.2.0\\opencv-4.2.0\\CudaBuild\\install\\x64\\vc16\\lib\\opencv_img_hash420.lib


LIBS += -LD:\opencv-4.2.0\opencv-4.2.0\CudaBuild\lib\Release\
            -lopencv_world420 \
            -lopencv_img_hash420\

        # Projects > Build & Run > Run
        # Check: add build library search path to PATH
        # This allows OpenCV DLLs to be found when running this application
LIBS += -L"D:\\opencv-4.2.0\\opencv-4.2.0\\CudaBuild\\install\\x64\\vc16\\bin"


#LIBS += -L"C:\\Program Files\\Basler\\pylon 5\\Runtime\\x64"


INCLUDEPATH += "E:\basler\Development\include"
LIBS += -L"E:\basler\Development\lib\x64\GCBase_MD_VC141_v3_1_Basler_pylon.lib"
LIBS += -L"E:\basler\Development\lib\x64\GenApi_MD_VC141_v3_1_Basler_pylon.lib"
LIBS += -L"E:\basler\Development\lib\x64\PylonBase_v6_3.lib"
LIBS += -L"E:\basler\Development\lib\x64\PylonC.lib"
LIBS += -L"E:\basler\Development\lib\x64\PylonGUI_v6_3.lib"
LIBS += -L"E:\basler\Development\lib\x64\PylonUtility_v6_3.lib"



win32:CONFIG(release, debug|release): LIBS += \
    -L$$PWD/Lib/Build64/release/ \
    -L"E:/basler/Development/lib/x64" \

else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$PWD/Lib/Build64/debug/ \
    -L"E:/basler/Development/lib/x64"


INCLUDEPATH += "E:/basler/Development/include"
#INCLUDEPATH += "C:/Program Files/Basler/pylon 6/Development/include"

DEPENDPATH += Lib/
DEPENDPATH += Lib/Build64/
#DEPENDPATH += "C:/Program Files/Basler/pylon 6/Runtime/x64"
DEPENDPATH += "E:/basler/Runtime/x64"

RESOURCES += \
    image.qrc




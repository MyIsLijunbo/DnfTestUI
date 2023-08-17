QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    applicationcontrol.cpp \
    basegamethread.cpp \
    easytemplate.cpp \
    gamebehavioranalysis.cpp \
    main.cpp \
    mainwindow.cpp \
    peripheralcontrol.cpp \
    player.cpp \
    screencapturewin.cpp \
    yolo.cpp

HEADERS += \
    GlobalValue.h \
    applicationcontrol.h \
    basegamethread.h \
    easytemplate.h \
    gamebehavioranalysis.h \
    mainwindow.h \
    peripheralcontrol.h \
    player.h \
    screencapturewin.h \
    yolo.h

FORMS += \
    mainwindow.ui


msvc {
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/opencv_4.8/include




win32: LIBS += -L$$PWD/opencv_4.8/lib/ \
                -llibopencv_core480d.dll \
                -llibopencv_calib3d480d.dll \
                -llibopencv_dnn480d.dll \
                -llibopencv_features2d480d.dll \
                -llibopencv_flann480d.dll \
                -llibopencv_highgui480d.dll \
                -llibopencv_imgcodecs480d.dll \
                -llibopencv_ml480d.dll \
                -llibopencv_flann480d.dll \
                -llibopencv_objdetect480d.dll \
                -llibopencv_photo480d.dll \
                -llibopencv_stitching480d.dll \
                -llibopencv_ts480d \
                -llibopencv_video480d.dll \
                -llibopencv_videoio480d.dll \
                -llibopencv_imgproc480d\

INCLUDEPATH += $$PWD/opencv_4.8/lib
DEPENDPATH += $$PWD/opencv_4.8/lib

#win32:!win32-g++: PRE_TARGETDEPS += $$PWD/opencv_4.8/lib/libopencv_core480d.dll.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/opencv_4.8/lib/liblibopencv_core480d.dll.a


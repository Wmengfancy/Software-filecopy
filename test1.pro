QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    choose.cpp \
    filecompressor.cpp \
    fileinfo.cpp \
    filepacker.cpp \
    inoderecorder.cpp \
    main.cpp \
    mainwindow.cpp \
    register1.cpp \
    up_down.cpp

HEADERS += \
    choose.h \
    common.h \
    filecompressor.h \
    fileinfo.h \
    filepacker.h \
    inoderecorder.h \
    mainwindow.h \
    register1.h \
    up_down.h

FORMS += \
    choose.ui \
    mainwindow.ui \
    register1.ui
RESOURCES += \
    image.qrc \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

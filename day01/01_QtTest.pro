



#模块
QT       += core gui

#高于4的版本，添加QT += widgets，为了兼容Qt4↓
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
# disables all the APIs deprecated before Qt 6.0.0

#应用程序的名字
TARGET = Helloworld

#指定makefile的英型,app
TEMPLATE = app

#源文件.cpp文件
SOURCES += \
    main.cpp \
    mywidget.cpp

#头文件.h文件
HEADERS += \
    mywidget.h

TRANSLATIONS += \
    first_project_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

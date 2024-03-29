QT       += core gui

INCLUDEPATH +=\
        C:\Qt\Tools\OpenSSL\Win_x64\include

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addpasslog.cpp \
    cryptocontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    passlistwindow.cpp

LIBS += \
        C:\Qt\Tools\OpenSSL\Win_x64\lib\libcrypto.lib \
        C:\Qt\Tools\OpenSSL\Win_x64\lib\libssl.lib

HEADERS += \
    addpasslog.h \
    cryptocontroller.h \
    mainwindow.h \
    passlistwindow.h

FORMS += \
    addpasslog.ui \
    mainwindow.ui \
    passlistwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    cridentials.enc

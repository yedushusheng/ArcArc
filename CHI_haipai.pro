QT       += core gui sql xml opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = CHI
TEMPLATE = app

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    datainputpanel.cpp \
    imageprocessing.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    password.cpp \
    printer.cpp \
    resultdisplay.cpp \
    sqliteoperator.cpp \
    userguidiance.cpp

HEADERS += \
    about.h \
    datainputpanel.h \
    imageprocessing.h \
    login.h \
    mainwindow.h \
    password.h \
    printer.h \
    resultdisplay.h \
    sqliteoperator.h \
    userguidiance.h

FORMS += \
    about.ui \
    datainputpanel.ui \
    login.ui \
    mainwindow.ui \
    password.ui \
    resultdisplay.ui \
    userguidiance.ui

RC_FILE += Detector.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    menu.qrc

DISTFILES += \
    README.md

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opencv4.8.0/opencv/build/x64/vc16/lib/ -lopencv_world480
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opencv4.8.0/opencv/build/x64/vc16/lib/ -lopencv_world480d

INCLUDEPATH += $$PWD/../../../opencv4.8.0/opencv/build/include
DEPENDPATH += $$PWD/../../../opencv4.8.0/opencv/build/x64/vc16

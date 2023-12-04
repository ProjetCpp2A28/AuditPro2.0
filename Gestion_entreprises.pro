QT       += core gui
QT       += sql

QT       += multimediawidgets charts printsupport widgets axcontainer network
QT += widgets network
QT += widgets

QT       +=network
QT       += core gui network charts
QT += serialport



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connection.cpp \
    entreprise.cpp \
    main.cpp \
    mainwindow_entreprises.cpp \
    smtp.cpp \
    stardelegate.cpp \
    stareditor.cpp \
    starrating.cpp \
    stat_combo.cpp

HEADERS += \
    arduino.h \
    connection.h \
    entreprise.h \
    mainwindow_entreprises.h \
    smtp.h \
    stardelegate.h \
    stareditor.h \
    starrating.h \
    stat_combo.h

FORMS += \
    mainwindow_entreprises.ui \
    stat_combo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

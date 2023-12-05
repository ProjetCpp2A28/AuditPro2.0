QT += core gui sql
QT += quick

QT += charts
QT += widgets
QT += printsupport
QT += serialport

QT += widgets network
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chart.cpp \
    drilldownchart.cpp \
    drilldownslice.cpp \
    entreprise.cpp \
    arduino.cpp \
    connection.cpp \
    employe.cpp \
    interface_employee.cpp \
    interface_rapport.cpp \
    main.cpp \
    mainwindow.cpp \
    rapport.cpp \
    reclamation.cpp \
    reglement.cpp \
    sms.cpp \
    smtp.cpp \
    stat_combo.cpp \
    statistique.cpp \
    welcome.cpp

HEADERS += \
    chart.h \
    drilldownchart.h \
    drilldownslice.h \
    entreprise.h \
    arduino.h \
    connection.h \
    employe.h \
    interface_employee.h \
    interface_rapport.h \
    mainwindow.h \
    rapport.h \
    reclamation.h \
    reglement.h \
    sms.h \
    smtp.h \
    stat_combo.h \
    statistique.h \
    welcome.h

FORMS += \
    interface_employee.ui \
    interface_rapport.ui \
    mainwindow.ui \
    stat_combo.ui \
    statistique.ui \
    welcome.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Regress
TEMPLATE = app
RESOURCES += resources.qrc
win32: RC_ICONS = regress.ico

CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    qcustomplot.cpp \
    randomvaluesdialog.cpp \
    regress.cpp \
    shareddata.cpp

HEADERS += \
    SharedData.h \
    qcustomplot.h \
    randomvaluesdialog.h \
    regress.h \
    shareddata.h

FORMS += \
    randomvaluesdialog.ui \
    regress.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

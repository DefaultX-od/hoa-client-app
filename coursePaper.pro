QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    booldatamodelrus.cpp \
    dbconnector.cpp \
    dialogaddrow.cpp \
    dialogconfirmation.cpp \
    dialogshowreceiptdetails.cpp \
    library.cpp \
    main.cpp \
    mainwindow.cpp \
    monthdatamodel.cpp

HEADERS += \
    booldatamodelrus.h \
    dbconnector.h \
    dialogaddrow.h \
    dialogconfirmation.h \
    dialogshowreceiptdetails.h \
    library.h \
    mainwindow.h \
    monthdatamodel.h

FORMS += \
    dialogaddrow.ui \
    dialogconfirmation.ui \
    dialogshowreceiptdetails.ui \
    mainwindow.ui

unix:INCLUDEPATH += /usr/include/postgresql
unix:LIBS += -L/usr/lib -lpq

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

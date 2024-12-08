QT += core gui serialport
QT += sql
QT += charts
QT += core gui widgets charts
QT += printsupport
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Employes.cpp \
    acceuil.cpp \
    arduino.cpp \
    connexion.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Employes.h \
    acceuil.h \
    arduino.h \
    connexion.h \
    mainwindow.h

FORMS += \
    acceuil.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc \
    icones.qrc \
    img/logo.qrc

DISTFILES += \
    ../../../Downloads/2.png

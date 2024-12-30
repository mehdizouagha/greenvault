QT       += core gui printsupport
QT += multimedia
QT += sql
QT += core gui charts
QT += core gui widgets  # Ajoutez 'widgets' si nécessaire
QT += charts
QT+=serialport

include("C:\Users\pc\Downloads\Qt-QrCodeGenerator-main\Qt-QrCodeGenerator-main\Qt-QrCodeGenerator.pri")
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    calendrierconge.cpp \
    client.cpp \
    commande.cpp \
    congesmanager.cpp \
    connexion.cpp \
    login.cpp \
    equipement.cpp\
    main.cpp \
    personel.cpp \
    secondwindow.cpp \
    stock.cpp

HEADERS += \
    arduino.h \
    calendrierconge.h \
    client.h \
    commande.h \
    congesmanager.h \
    connexion.h \
    login.h \
    equipement.h\
    personel.h \
    secondwindow.h \
    stock.h

FORMS += \
    login.ui \
    secondwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    boite.qrc \
    boite.qrc \
    boite.qrc \
    boite2.qrc \
    boite2.qrc \
    boite3.qrc \
    client.qrc \
    commande.qrc \
    commande2.qrc \
    equipement.qrc \
    equipement2.qrc \
    equipement2.qrc \
    equipement2.qrc \
    img.qrc \
    personnel.qrc \
    personnel.qrc \
    personnel.qrc \
    personnel2.qrc

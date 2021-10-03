QT       += core gui sql multimedia printsupport charts network serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abonnement.cpp \
    arduino.cpp \
    client.cpp \
    commande.cpp \
    connexion.cpp \
    dialog.cpp \
    employe.cpp \
    fournisseur.cpp \
    main.cpp \
    mainwindow.cpp \
    produit.cpp \
    profil.cpp \
    reclamation.cpp \
    stock.cpp \
    vehicule.cpp

HEADERS += \
    abonnement.h \
    arduino.h \
    client.h \
    commande.h \
    connexion.h \
    dialog.h \
    employe.h \
    fournisseur.h \
    mainwindow.h \
    produit.h \
    profil.h \
    reclamation.h \
    stock.h \
    vehicule.h

FORMS += \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

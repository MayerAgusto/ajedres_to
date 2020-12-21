QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bishop.cpp \
    CBoton.cpp \
    Coordenada.cpp \
    Horse.cpp \
    King.cpp \
    Movimientos.cpp \
    Pawn.cpp \
    Piece.cpp \
    Queen.cpp \
    Rook.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Bishop.h \
    CBoton.h \
    Coordenada.h \
    Horse.h \
    King.h \
    Movimientos.h \
    Pawn.h \
    Piece.h \
    Queen.h \
    Rook.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recursos.qrc

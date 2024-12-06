QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 moc

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chessboard.cpp \
    draggablepiece.cpp \
    foolsmate.cpp \
    main.cpp \
    startmenu.cpp

HEADERS += \
    chessboard.h \
    draggablepiece.h \
    foolsmate.h \
    startmenu.h

FORMS += \
    startmenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    Fools-Mate.png \
    stockfish-windows-x86-64-sse41-popcnt.exe \
    stockfish.exe

#-------------------------------------------------
#
# Project created by QtCreator 2020-04-27T13:34:32
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeatherApp
TEMPLATE = app

LIBS += -lopengl32

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    Drawing/drawdata.cpp \
    Drawing/grid.cpp \
    Drawing/text.cpp \
    data.cpp \
        main.cpp \
    Coordinates/geocoordinates.cpp \
    Coordinates/flatcoordinates.cpp \
    mainwindow.cpp \
    Coordinates/converter.cpp \
    Coordinates/openglcoordinates.cpp \
    pointdata.cpp

HEADERS += \
    Coordinates/geocoordinates.h \
    Coordinates/flatcoordinates.h \
    Drawing/drawdata.h \
    Drawing/grid.h \
    Drawing/text.h \
    data.h \
    mainwindow.h \
    Coordinates/converter.h \
    Coordinates/openglcoordinates.h \
    pointdata.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




DISTFILES += \
    fonts/ARIALN.TTF \
    fonts/ARIALNB.TTF \
    fonts/ARIALNBI.TTF \
    fonts/ARIALNI.TTF \
    fonts/ITCBLKAD.TTF \
    fonts/VIVALDII.TTF \
    fonts/arial.ttf \
    fonts/arialbd.ttf \
    fonts/arialbi.ttf \
    fonts/ariali.ttf \
    fonts/ariblk.ttf \
    sh.fsh \
    sh.vsh

unix|win32: LIBS += -L$$PWD/includes/testLIB/lib/ -lparser

INCLUDEPATH += $$PWD/includes/testLIB/include
DEPENDPATH += $$PWD/includes/testLIB/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/includes/freetype-windows-binaries-master/win64/ -lfreetype
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/includes/freetype-windows-binaries-master/win64/ -lfreetype
else:unix: LIBS += -L$$PWD/includes/freetype-windows-binaries-master/win64/ -lfreetype

INCLUDEPATH += $$PWD/includes/freetype-windows-binaries-master/include
DEPENDPATH += $$PWD/includes/freetype-windows-binaries-master/include

unix|win32: LIBS += -L$$PWD/includes/glew-2.1.0-win32/glew-2.1.0/lib/Release/x64/ -lglew32s

INCLUDEPATH += $$PWD/includes/glew-2.1.0-win32/glew-2.1.0/include/GL
DEPENDPATH += $$PWD/includes/glew-2.1.0-win32/glew-2.1.0/include/GL

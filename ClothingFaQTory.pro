QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

SOURCES = $$files("src/*.cpp", true)
HEADERS = $$files("src/*.h", true)

FORMS += $$files("src/*.ui", true)

# enable or disable qt logging
CONFIG += develop
CONFIG(release, develop|release): DEFINES += QT_NO_DEBUG_OUTPUT
CONFIG(release, develop|release): DEFINES += QT_NO_INFO_OUTPUT
CONFIG(release, develop|release): DEFINES += QT_NO_WARNING_OUTPUT

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

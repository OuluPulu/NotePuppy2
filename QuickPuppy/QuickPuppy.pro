TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    puppycore.cpp \
    puppyfilesystemmodel.cpp \
    puppyfile.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    puppycore.h \
    puppyfilesystemmodel.h \
    puppyfile.h

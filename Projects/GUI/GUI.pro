QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/include

SOURCES += \
    Source/main.cpp \
    Source/MainWindow.cpp \
    Source/RTColorWidget.cpp

HEADERS += \
    Include/MainWindow.hh \
    Include/RTColorWidget.hh

FORMS += \
    Form/MainWindow.ui \
    Form/RTColorWidget.ui

#RESOURCES += 

defineReplace(prependAll) {
 for(a,$$1):result += $$2$${a}$$3
 return($$result)
}

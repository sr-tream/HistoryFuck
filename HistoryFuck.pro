#-------------------------------------------------
#
# Project created by QtCreator 2017-05-05T15:29:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HistoryFuck
TEMPLATE = app
TRANSLATIONS += language_English.ts \
				language_Russian.ts
CODECFORSRC     = UTF-8

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
		interface.cpp

HEADERS  += interface.h

FORMS    += interface.ui

DISTFILES += \
    language_English.ts \
    language_Russian.ts

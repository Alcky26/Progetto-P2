QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Data/annotazione.cpp \
    Data/elenco.cpp \
    Data/nota.cpp \
    Data/promemoria.cpp \
    Data/ricorrenza.cpp \
    Data/spesa.cpp \
    Util/lista.cpp \
    Util/nodo.cpp \
    Util/type_elenco.cpp \
    Util/type_spesa.cpp \
    View/Widget/wannotazione.cpp \
    View/example.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Data/annotazione.h \
    Data/elenco.h \
    Data/nota.h \
    Data/promemoria.h \
    Data/ricorrenza.h \
    Data/spesa.h \
    Util/lista.h \
    Util/nodo.h \
    Util/type_elenco.h \
    Util/type_spesa.h \
    View/Widget/wannotazione.h \
    View/example.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

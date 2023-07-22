QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/items/iwad.cpp \
    src/items/modfile.cpp \
    src/items/preset.cpp \
    src/items/sourceport.cpp \
    src/items/wad.cpp \
    src/main.cpp \
    src/models/iwad_model.cpp \
    src/models/map_model.cpp \
    src/models/modfile_model.cpp \
    src/models/preset_model.cpp \
    src/models/sourceport_model.cpp \
    src/views/mainwindow.cpp \
    src/views/mainwindow_tab1.cpp \
    src/views/mainwindow_tab2.cpp \
    src/views/formdialog.cpp \
    src/views/mainwindow_tab3.cpp

HEADERS += \
    src/exceptions.h \
    src/items/iwad.h \
    src/items/modfile.h \
    src/items/preset.h \
    src/items/sourceport.h \
    src/items/wad.h \
    src/models/iwad_model.h \
    src/models/map_model.h \
    src/models/modfile_model.h \
    src/models/preset_model.h \
    src/models/sourceport_model.h \
    src/views/mainwindow.h \
    src/views/formdialog.h \

FORMS += \
    forms/formdialog.ui \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

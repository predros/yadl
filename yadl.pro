QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/models/iwad.cpp \
    src/models/modfile.cpp \
    src/models/preset.cpp \
    src/models/sourceport.cpp \
    src/models/wad.cpp \
    src/main.cpp \
    src/controllers/iwad_controller.cpp \
    src/controllers/map_controller.cpp \
    src/controllers/modfile_controller.cpp \
    src/controllers/preset_controller.cpp \
    src/controllers/sourceport_controller.cpp \
    src/views/mainwindow.cpp \
    src/views/mainwindow_tab1.cpp \
    src/views/mainwindow_tab2.cpp \
    src/views/formdialog.cpp \
    src/views/mainwindow_tab3.cpp

HEADERS += \
    src/exceptions.h \
    src/models/iwad.h \
    src/models/modfile.h \
    src/models/preset.h \
    src/models/sourceport.h \
    src/models/wad.h \
    src/controllers/iwad_controller.h \
    src/controllers/map_controller.h \
    src/controllers/modfile_controller.h \
    src/controllers/preset_controller.h \
    src/controllers/sourceport_controller.h \
    src/views/mainwindow.h \
    src/views/formdialog.h \

FORMS += \
    forms/formdialog.ui \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

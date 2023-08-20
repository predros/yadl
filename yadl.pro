QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include

SOURCES += \
    src/main.cpp \
    src/models/iwad.cpp \
    src/models/modfile.cpp \
    src/models/preset.cpp \
    src/models/sourceport.cpp \
    src/models/wad.cpp \
    src/controllers/iwad_controller.cpp \
    src/controllers/map_controller.cpp \
    src/controllers/modfile_controller.cpp \
    src/controllers/preset_controller.cpp \
    src/controllers/sourceport_controller.cpp \
    src/views/mainwindow/mainwindow.cpp \
    src/views/mainwindow/methods_io.cpp \
    src/views/mainwindow/methods_iwad.cpp \
    src/views/mainwindow/methods_launcher.cpp \
    src/views/mainwindow/methods_preset.cpp \
    src/views/mainwindow/methods_sourceport.cpp \
    src/views/mainwindow/slots_tab1.cpp \
    src/views/mainwindow/slots_tab2.cpp \
    src/views/mainwindow/slots_tab3.cpp \
    src/views/formdialog/formdialog.cpp

HEADERS += \
    include/exceptions.h \
    include/models/iwad.h \
    include/models/modfile.h \
    include/models/preset.h \
    include/models/sourceport.h \
    include/models/wad.h \
    include/controllers/iwad_controller.h \
    include/controllers/map_controller.h \
    include/controllers/modfile_controller.h \
    include/controllers/preset_controller.h \
    include/controllers/sourceport_controller.h \
    include/views/mainwindow.h \
    include/views/formdialog.h

FORMS += \
    forms/formdialog.ui \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/assets.qrc

RC_ICONS = assets/yadl.ico

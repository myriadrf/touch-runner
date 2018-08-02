#-------------------------------------------------
#
# Project created by QtCreator 2018-07-25T13:46:40
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = TouchRunner
DESTDIR = $${OUT_PWD}/TouchRunner
#TARGET.path = $$PREFIX/
TEMPLATE = app



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
        main.cpp \
        mainwindow.cpp \
        about_dialog.cpp \
    Button.cpp \
    ButtonList.cpp

HEADERS += \
    about_dialog.h \
    mainwindow.h \
    Button.h \
    ButtonList.h

FORMS += \
        mainwindow.ui \
        about_dialog.ui

LIBS += -lqtermwidget5 -L/usr/lib64/


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


configuration.path = /opt/$${TARGET}/config
configuration.files = config/config.json

!exists(/opt/$${TARGET}/config/config.json) {
    INSTALLS += configuration
    message("No old configuration detected.")
}



DISTFILES += \
    config/config.json

RESOURCES += \
    icons.qrc







defineTest(copyToDestDir) {
    files = $$1

    for(FILE, files) {
        DDIR = $$DESTDIR
                    FILE = $$absolute_path($$FILE)

        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}

copyToDestDir($${DISTFILES})




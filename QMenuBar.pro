QT    += core gui sql




greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminportaldialog.cpp \
    assignmentdialog.cpp \
    closeticket.cpp \
    contactcard.cpp \
    createdb.cpp \
    customerlist.cpp \
    databasemanager.cpp \
    databasesetup.cpp \
    emaildialog.cpp \
    home.cpp \
    homewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindow1.cpp \
    secdialog.cpp

HEADERS += \
    adminportaldialog.h \
    assignmentdialog.h \
    closeticket.h \
    contactcard.h \
    customerlist.h \
    databasemanager.h \
    databasesetup.h \
    emaildialog.h \
    home.h \
    homewindow.h \
    mainwindow.h \
    mainwindow1.h \
    secdialog.h \
    ticketdata.h

FORMS += \
    adminportaldialog.ui \
    assignmentdialog.ui \
    closeticket.ui \
    contactcard.ui \
    customerlist.ui \
    emaildialog.ui \
    form.ui \
    home.ui \
    homewindow.ui \
    mainwindow.ui \
    mainwindow1.ui \
    secdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    ../../../Downloads/Vector (1).png \
    Ticket.txt

# Platform-specific library names
# For Windows
win32: LIBS += -L"C:/Users/kelvi/OneDrive/Documents/QMenuBar" -lsqlite3

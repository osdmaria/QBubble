QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    src/delegate/alliesgamecontroller.cpp \
    src/delegate/enemiesgamecontroller.cpp \
    src/delegate/maincontroller.cpp \
    src/delegate/sologamecontroller.cpp \
    src/delegate/windowscontroller.cpp \
    src/model/bubble.cpp \
    src/model/canonmodel.cpp \
    src/model/coloredbubble.cpp \
    src/model/containermodel.cpp \
    src/model/explosivebubble.cpp \
    src/model/generatormodel.cpp \
    src/model/hexgridmodel.cpp \
    src/model/indestructiblebubble.cpp \
    src/model/scoremodel.cpp \
    src/view/alliesgamewindow.cpp \
    src/view/bubbleview.cpp \
    src/view/canonwidget.cpp \
    src/view/containerwidget.cpp \
    src/view/enemiesgamewindow.cpp \
    src/view/gridscene.cpp \
    src/view/howtoplaywindow.cpp \
    src/view/mainmenuwindow.cpp \
    src/view/multiplayerchoicewindow.cpp \
    src/view/music.cpp \
    src/view/scorewidget.cpp \
    src/view/sologamewindow.cpp


HEADERS += \
    src/delegate/alliesgamecontroller.h \
    src/delegate/enemiesgamecontroller.h \
    src/delegate/maincontroller.h \
    src/delegate/sologamecontroller.h \
    src/delegate/windowscontroller.h \
    src/model/bubble.h \
    src/model/canonmodel.h \
    src/model/coloredbubble.h \
    src/model/containermodel.h \
    src/model/explosivebubble.h \
    src/model/generatormodel.h \
    src/model/hexgridmodel.h \
    src/model/indestructiblebubble.h \
    src/model/scoremodel.h \
    src/view/alliesgamewindow.h \
    src/view/bubbleview.h \
    src/view/canonwidget.h \
    src/view/containerwidget.h \
    src/view/enemiesgamewindow.h \
    src/view/gridscene.h \
    src/view/howtoplaywindow.h \
    src/view/mainmenuwindow.h \
    src/view/multiplayerchoicewindow.h \
    src/view/music.h \
    src/view/scorewidget.h \
    src/view/sologamewindow.h



#FORMS += \




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/resources/resources.qrc

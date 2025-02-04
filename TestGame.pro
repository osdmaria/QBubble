QT       += core gui
QT       += quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bubble/bubble.cpp \
    BubblesContainer/bubblescontainer.cpp \
    Canon/canon_widget.cpp \
    Grid/grid_logic.cpp \
    Grid/grid_view.cpp \
    Menu/menu.cpp \
    Menu/menumultijoueur.cpp \
    Menu/menuregles.cpp \
    Score/score.cpp \
    game_main_window.cpp \
    main.cpp

HEADERS += \
    Bubble/bubble.h \
    BubblesContainer/bubblescontainer.h \
    Canon/canon_widget.h \
    Grid/grid_logic.h \
    Grid/grid_view.h \
    Menu/menu.h \
    Menu/menumultijoueur.h \
    Menu/menuregles.h \
    Score/score.h \
    game_main_window.h

FORMS += \
    Bubble/bubble.ui \
    BubblesContainer/bubblescontainer.ui \
    Canon/canon_widget.ui \
    Menu/menu.ui \
    Menu/menumultijoueur.ui \
    Menu/menuregles.ui \
    Score/score.ui \
    game_main_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    Canon/Canon.pro \
    Grid/Grid.pro

RESOURCES += \
    ../../QBubble_score/QBubble_score/ressources.qrc \
    Bubble/Bulles.qrc \
    Canon/canon.qrc \
    Font/font.qrc \
    ressources.qrc

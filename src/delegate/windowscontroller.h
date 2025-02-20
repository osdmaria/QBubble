#ifndef WINDOWSCONTROLLER_H
#define WINDOWSCONTROLLER_H

#include "src/view/mainmenuwindow.h"
#include "src/view/howtoplaywindow.h"
#include "src/view/multiplayerchoicewindow.h"
#include "src/view/sologamewindow.h"
#include "src/view/alliesgamewindow.h"
#include "src/view/enemiesgamewindow.h"
#include "src/view/music.h"

#include "src/delegate/sologamecontroller.h"
#include "src//delegate//enemiesgamecontroller.h"
#include "src/delegate/alliesgamecontroller.h"

#include <QObject>
#include <QPushButton>
#include <QApplication>
#include <QScreen>
#include <QGuiApplication>


class WindowsController : public QObject
{
    Q_OBJECT
    int m_fixedWidth = 1125, m_fixedHeight = 642;
public:
    WindowsController(QObject *parent=nullptr);
    void setFixedSize(int width, int height, QMainWindow *window);
    MainMenuWindow *mainMenuWindow(){return m_mainMenuView;}
    HowToPlayWindow *howToplayWindow(){return m_howToPlayView;}
    MultiplayerChoiceWindow *multiplayerChoiceWindow(){return m_multiplayerChoiceView;}
    SoloGameWindow *soloGameWindow(){return m_soloGameView;}
    AlliesGameWindow *alliesGameWindow(){return m_alliesGameView;}
    EnemiesGameWindow *enemiesGameWindow(){return m_enemiesGameView;}
    SoloGameController *soloGameController(){return m_soloGameController;}
    EnemiesGameController *enemiesGameController(){return m_enemiesGameController;}
    AlliesGameController *alliesGameController(){return m_alliesGameController;}
    void startMusic();


signals:
    void soloLaunched();
    void soloEnded();

    void alliesLauched();
    void alliesEnded();

    void enemiesLauched();
    void enemiesEnded();


public slots:
    //Main menu window
    void openMainMenu();
    void openSoloGame();
    void openMultiplayerChoice();
    void openHowToPlay();
    void quit();

    //Multiplayer choice window
    void openEnemiesGameWindow();
    void openAlliesGameWindow();


    //pause and back main menu
    void handleRetour();
    void openPause();
    void closePause();
    void retry();

private:
    void connectSignalsMainMenu();
    void connectSignalsHowToplay();
    void connectSignalsMultiplayerChoice();
    void connectSignalsSolo();
    void connectSignalsEnemies();
    void connectSignalsAllies();

    MainMenuWindow *m_mainMenuView;
    HowToPlayWindow *m_howToPlayView;
    MultiplayerChoiceWindow *m_multiplayerChoiceView;
    SoloGameController *m_soloGameController;
    EnemiesGameController *m_enemiesGameController;
    AlliesGameController *m_alliesGameController;

    SoloGameWindow *m_soloGameView;
    AlliesGameWindow *m_alliesGameView;
    EnemiesGameWindow *m_enemiesGameView;
    Music *music;
};

#endif // WINDOWSCONTROLLER_H

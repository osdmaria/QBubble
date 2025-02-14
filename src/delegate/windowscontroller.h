#ifndef WINDOWSCONTROLLER_H
#define WINDOWSCONTROLLER_H

#include "src/view/mainmenuwindow.h"
#include "src/view/howtoplaywindow.h"
#include "src/view/multiplayerchoicewindow.h"
#include "src/view/sologamewindow.h"
#include "src/view/alliesgamewindow.h"
#include "src/view/enemiesgamewindow.h"
#include "src/view/music.h"

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
    void launch();
    void setFixedSize(int width, int height, QMainWindow *window);

    MainMenuWindow *mainMenuWindow(){return m_mainMenuView;}
    HowToPlayWindow *howToplayWindow(){return m_howToPlayView;}
    MultiplayerChoiceWindow *multiplayerChoiceWindow(){return m_multiplayerChoiceView;}
    SoloGameWindow *soloGameWindow(){return m_soloGameView;}
    void startMusic();


signals:
    void soloLaunched();
    void alliesLauched();
    void enemiesLauched();

public slots:
    //Main menu window
    void openSoloGame();
    void openMultiplayerChoice();
    void openHowToPlay();
    void quit();

    //Rules window
    void openMainMenuFromHowToPlay();

    //Multiplayer choice window
    void openMainMenuFromMultiplayerChoice();
    void openEnemiesGameWindow();
    void openAlliesGameWindow();

private:
    void connectSignalsMainMenu();
    void connectSignalsHowToplay();
    void connectSignalsMultiplayerChoice();

    MainMenuWindow *m_mainMenuView;
    HowToPlayWindow *m_howToPlayView;
    MultiplayerChoiceWindow *m_multiplayerChoiceView;

    SoloGameWindow *m_soloGameView;
    AlliesGameWindow *m_alliesGameView;
    EnemiesGameWindow *m_enemiesGameView;
    Music *music;
};

#endif // WINDOWSCONTROLLER_H

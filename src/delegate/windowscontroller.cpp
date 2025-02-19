#include "windowscontroller.h"
#include <QFile>

WindowsController::WindowsController(QObject *parent) :QObject(parent)
{
    m_mainMenuView = new MainMenuWindow();
    m_howToPlayView = new HowToPlayWindow();
    m_multiplayerChoiceView = new MultiplayerChoiceWindow();
    music = new Music();

    //Menu principal
    setFixedSize(m_fixedWidth,m_fixedHeight,m_mainMenuView);
    connectSignalsMainMenu();

    //Comment jouer
    setFixedSize(m_fixedWidth,m_fixedHeight,m_howToPlayView);
    connectSignalsHowToplay();

    //Choix Multijoueurs
    setFixedSize(m_fixedWidth,m_fixedHeight,m_multiplayerChoiceView);
    connectSignalsMultiplayerChoice();
}

void WindowsController::connectSignalsMainMenu(){
    qDebug() << "SignalsMainMenu clicked!";
    connect(m_mainMenuView, &MainMenuWindow::onSoloClicked, this, &WindowsController::openSoloGame);
    connect(m_mainMenuView, &MainMenuWindow::onMultiplayerClicked, this, &WindowsController::openMultiplayerChoice);
    connect(m_mainMenuView, &MainMenuWindow::onHowToPlayClicked, this, &WindowsController::openHowToPlay);
    connect(m_mainMenuView, &MainMenuWindow::onQuitClicked, this, &WindowsController::quit);
}

//LAUNCH
void WindowsController::launch(){
    m_mainMenuView->show();

}

//HOW TO PLAY -> Connect signals
void WindowsController::connectSignalsHowToplay(){
    connect(m_howToPlayView, &HowToPlayWindow::onMainMenuClicked, this, &WindowsController::openMainMenuFromHowToPlay);
}

//HOW TO PLAY -> open how to play menu
void WindowsController::openHowToPlay() {
    m_mainMenuView->hide();
    m_howToPlayView->show();
}

//HOW TO PLAY -> back to main menu
void WindowsController::openMainMenuFromHowToPlay() {
    m_howToPlayView->hide();
    m_mainMenuView->show();
}


//MULTIPLAYER CHOICE -> connect signals
void WindowsController::connectSignalsMultiplayerChoice(){
    connect(m_multiplayerChoiceView, &MultiplayerChoiceWindow::onMainMenuClicked, this, &WindowsController::openMainMenuFromMultiplayerChoice);
    connect(m_multiplayerChoiceView, &MultiplayerChoiceWindow::onAlliesClicked, this, &WindowsController::openAlliesGameWindow);
    connect(m_multiplayerChoiceView, &MultiplayerChoiceWindow::onEnemiesClicked, this, &WindowsController::openEnemiesGameWindow);
}

//MULTIPLAYER CHOICE -> open multiplayer choice
void WindowsController::openMultiplayerChoice() {
    m_mainMenuView->hide();
    m_multiplayerChoiceView->show();
}

void WindowsController::openMainMenuFromMultiplayerChoice() {
    m_multiplayerChoiceView->hide();
    m_mainMenuView->show();
}


//SOLO GAME -> openSolo
void WindowsController::openSoloGame() {
    m_soloGameView = new SoloGameWindow(m_fixedWidth,m_fixedHeight);
    m_mainMenuView->hide();
    m_soloGameView->show();
    emit soloLaunched();
}

void WindowsController::openAlliesGameWindow() {
    qDebug() << "Allies clicked!";
    m_alliesGameView = new AlliesGameWindow(m_fixedWidth,m_fixedHeight);
    m_multiplayerChoiceView->hide();
    m_alliesGameView->show();
    emit alliesLauched();
}

void WindowsController::openEnemiesGameWindow() {
    qDebug() << "Enemies clicked!";
    m_enemiesGameView = new EnemiesGameWindow(m_fixedWidth,m_fixedHeight);
    m_multiplayerChoiceView->hide();
    m_enemiesGameView->show();
    emit enemiesLauched();
}

void WindowsController::startMusic() {
    music->playBackgroundMusic( 0.5);
}



void WindowsController::quit() {
    QApplication::quit();
}


void WindowsController::setFixedSize(int width, int height, QMainWindow *window){
    window->setFixedSize(width,height);
}

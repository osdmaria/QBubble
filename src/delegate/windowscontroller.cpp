#include "windowscontroller.h"

WindowsController::WindowsController(QObject *parent) :QObject(parent)
{
    m_mainMenuView = new MainMenuWindow();
    m_howToPlayView = new HowToPlayWindow();
    m_multiplayerChoiceView = new MultiplayerChoiceWindow();
    m_soloGameView = new SoloGameWindow();
    m_alliesGameView = new AlliesGameWindow();
    m_enemiesGameView = new EnemiesGameWindow();


    //Menu principal
    connectSignalsMainMenu();
    setFixedSize(m_mainMenuView);

    //Comment jouer
    connectSignalsHowToplay();
    setFixedSize(m_howToPlayView);

    //Choix Multijoueurs
    connectSignalsMultiplayerChoice();
    setFixedSize(m_multiplayerChoiceView);

    //Solo
    setFixedSize(m_soloGameView);

    //Allies
    setFixedSize(m_alliesGameView);

    //Enemies
    setFixedSize(m_enemiesGameView);
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

    m_mainMenuView->hide();
    m_soloGameView->show();
    emit soloLaunched();
}

void WindowsController::openAlliesGameWindow() {
    qDebug() << "Allies clicked!";
    m_multiplayerChoiceView->hide();
    m_alliesGameView->show();
    emit alliesLauched();
}

void WindowsController::openEnemiesGameWindow() {
    qDebug() << "Enemies clicked!";
    m_multiplayerChoiceView->hide();
    m_enemiesGameView->show();
    emit enemiesLauched();
}



void WindowsController::quit() {
    QApplication::quit();
}

void WindowsController::setFixedSize(QMainWindow *w){

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    int width = screenGeometry.width() * 0.8;
    int height = screenGeometry.height() * 0.8;

    w->setFixedSize(640,750);
}

#include "maincontroller.h"
#include <QTimer>

MainController::MainController(QObject *parent)
    : QObject{parent}
{
    m_windowsController = new WindowsController();

    m_windowsController->launch();
    m_windowsController->startMusic();
    //QTimer::singleShot(500, m_windowsController, &WindowsController::startMusic);
    connect(m_windowsController->mainMenuWindow(), &MainMenuWindow::onSoloClicked, this, &MainController::soloLaunched);
    connect(m_windowsController->multiplayerChoiceWindow(), &MultiplayerChoiceWindow::onEnemiesClicked, this, &MainController::enemieLaunched);
    connect(m_windowsController->multiplayerChoiceWindow(), &MultiplayerChoiceWindow::onAlliesClicked, this, &MainController::allieLaunched);
}

MainController::~MainController() {
    delete m_windowsController;
    delete m_soloGameController;
    delete m_enemieGameController;
    delete m_alliesGameController;
}


void MainController::soloLaunched(){
    m_soloGameController = new SoloGameController(m_windowsController->soloGameWindow(),m_windowsController->mainMenuWindow());
    m_soloGameController->start();
}

void MainController::soloEnded(){
    delete m_soloGameController;
}

void MainController::enemieLaunched(){
    m_enemieGameController = new EnemiesGameController(m_windowsController->enemiesGameWindow(),m_windowsController->mainMenuWindow());
    m_enemieGameController->start();
}

void MainController::enemieEnded(){
    delete m_enemieGameController;
}

void MainController::allieLaunched(){
    m_alliesGameController = new AlliesGameController(m_windowsController->alliesGameWindow(),m_windowsController->mainMenuWindow());
    m_alliesGameController->start();
}

void MainController::allieEnded(){
    delete m_alliesGameController;
}

#include "maincontroller.h"
#include <QTimer>

MainController::MainController(QObject *parent)
    : QObject{parent}
{
    m_windowsController = new WindowsController();
    m_windowsController->openMainMenu();
    m_windowsController->startMusic();

    //QTimer::singleShot(500, m_windowsController, &WindowsController::startMusic);
    connect(m_windowsController, &WindowsController::soloLaunched, this, &MainController::soloLaunched);
    connect(m_windowsController, &WindowsController::alliesLauched, this, &MainController::allieLaunched);
    connect(m_windowsController, &WindowsController::enemiesLauched, this, &MainController::enemieLaunched);

    connect(m_windowsController, &WindowsController::soloEnded, this, &MainController::soloEnded);
    connect(m_windowsController, &WindowsController::alliesEnded, this, &MainController::allieEnded);
    connect(m_windowsController, &WindowsController::enemiesEnded, this, &MainController::enemieEnded);


}

MainController::~MainController() {
    // delete m_windowsController;
    // delete m_soloGameController;
    // delete m_enemieGameController;
    // delete m_alliesGameController;
}


void MainController::soloLaunched() {

    m_soloGameController = new SoloGameController(m_windowsController->soloGameWindow(), this);

    connect(m_soloGameController, &SoloGameController::requestLevelSelection, m_windowsController, &WindowsController::showLevelMenu);
    connect(m_windowsController, &WindowsController::sendSelectedLevel, m_soloGameController, &SoloGameController::start);
    m_soloGameController->startLevelSelection();

    connect(m_soloGameController, &SoloGameController::showGameOver, m_windowsController, &WindowsController::handleGameOver);


}



void MainController::soloEnded(){
    delete m_soloGameController;
}

void MainController::enemieLaunched(){
    m_enemieGameController = new EnemiesGameController(m_windowsController->enemiesGameWindow(),this);
    connect(m_enemieGameController, &EnemiesGameController::requestLevelSelection, m_windowsController, &WindowsController::showLevelMenu);
    connect(m_windowsController, &WindowsController::sendSelectedLevel, m_enemieGameController, &EnemiesGameController::start);
    m_enemieGameController->startLevelSelection();
    connect(m_enemieGameController, &EnemiesGameController::showGameOver, m_windowsController, &WindowsController::handleGameOver);
}

void MainController::enemieEnded(){
    delete m_enemieGameController;
}

void MainController::allieLaunched(){
    m_alliesGameController = new AlliesGameController(m_windowsController->alliesGameWindow(),this);
    connect(m_alliesGameController, &AlliesGameController::requestLevelSelection, m_windowsController, &WindowsController::showLevelMenu);
    connect(m_windowsController, &WindowsController::sendSelectedLevel, m_alliesGameController, &AlliesGameController::start);
    m_alliesGameController->startLevelSelection();
    connect(m_alliesGameController, &AlliesGameController::showGameOver, m_windowsController, &WindowsController::handleGameOver);
}

void MainController::allieEnded(){
    delete m_alliesGameController;
}

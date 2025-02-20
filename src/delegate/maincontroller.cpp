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

    //changer c'est le windows controller qui doit envoyer les signaux
    qDebug() << "Checking multiplayerChoiceWindow:" << m_windowsController->multiplayerChoiceWindow();

    //connect(m_windowsController->multiplayerChoiceWindow(), &MultiplayerChoiceWindow::onEnemiesClicked, this, &MainController::enemieLaunched);
    //connect(m_windowsController->multiplayerChoiceWindow(), &MultiplayerChoiceWindow::onAlliesClicked, this, &MainController::allieLaunched);

    connect(m_windowsController, &WindowsController::soloEnded, this, &MainController::soloEnded);
    connect(m_windowsController, &WindowsController::alliesEnded, this, &MainController::allieEnded);
    connect(m_windowsController, &WindowsController::enemiesEnded, this, &MainController::enemieEnded);
}

MainController::~MainController() {
    delete m_windowsController;
    delete m_soloGameController;
    delete m_enemieGameController;
    delete m_alliesGameController;
}


void MainController::soloLaunched() {
    qDebug() << "Launching Solo Game...";

    m_soloGameController = new SoloGameController(m_windowsController->soloGameWindow(), this);
    m_soloGameController->startLevelSelection();
}



void MainController::soloEnded(){
    delete m_soloGameController;
}

void MainController::enemieLaunched(){
    qDebug() << "Launching enemies Game...";
    m_enemieGameController = new EnemiesGameController(m_windowsController->enemiesGameWindow(),this);
    m_enemieGameController->startLevelSelection();
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

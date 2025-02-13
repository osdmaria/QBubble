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
}

MainController::~MainController() {
    delete m_windowsController;
    delete m_soloGameController;
}


void MainController::soloLaunched(){
    m_soloGameController = new SoloGameController(m_windowsController->soloGameWindow(),m_windowsController->mainMenuWindow());
}

void MainController::soloEnded(){
    delete m_soloGameController;
}

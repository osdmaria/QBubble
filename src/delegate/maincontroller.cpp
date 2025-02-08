#include "maincontroller.h"


MainController::MainController(QObject *parent)
    : QObject{parent}
{
    m_windowsController = new WindowsController();

    m_windowsController->launch();

    connect(m_windowsController->mainMenuWindow(), &MainMenuWindow::onSoloClicked, this, &MainController::soloLaunched);
}

MainController::~MainController() {
    delete m_windowsController;
    delete m_soloGameController;
}


void MainController::soloLaunched(){
    m_soloGameController = new SoloGameController(m_windowsController->soloGameWindow());
}

void MainController::soloEnded(){
    delete m_soloGameController;
}

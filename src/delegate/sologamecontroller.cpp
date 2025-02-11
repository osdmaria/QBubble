#include "sologamecontroller.h"

SoloGameController::SoloGameController(SoloGameWindow *soloGameView,MainMenuWindow *mainMenuView, QObject *parent)
    : QObject{parent}, m_soloGameView{soloGameView}, m_mainMenuView{mainMenuView}
{
    m_scoreModel = new ScoreModel();
    m_containerModel = new ContainerModel();

    connect(m_scoreModel, &ScoreModel::scoreChanged, this, &SoloGameController::updateScore);

    //connectsignal des buttons
    connectSignalsButttons();
}

SoloGameController::~SoloGameController(){
    delete m_scoreModel;
}


void SoloGameController::updateScore(int x)
{
    m_soloGameView->scoreWidget()->updateLabel(x);
}

void SoloGameController::connectSignalsButttons(){
    qDebug() << "retour clicked!";
    connect(m_soloGameView, &SoloGameWindow::onRetourClicked, this, &SoloGameController::openMainMenu);
    //connect(m_mainMenuView, &SoloGameWindow::onPauseClicked, this, &SoloGameController::);
}

void SoloGameController::openMainMenu() {

    m_soloGameView->hide();
    m_mainMenuView->show();
    emit menuLauched();
}

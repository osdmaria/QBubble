#include "sologamecontroller.h"

SoloGameController::SoloGameController(SoloGameWindow *soloGameView,MainMenuWindow *mainMenuView, QObject *parent)
    : QObject{parent}, m_soloGameView{soloGameView}, m_mainMenuView{mainMenuView}
{
    m_scoreModel = new ScoreModel();
    m_containerModel = new ContainerModel();
    connect(m_scoreModel, &ScoreModel::scoreChanged, this, &SoloGameController::updateScore);
    connectSignalsButttons();
    //ajout important pour éviter le crash de l'appli
    m_pauseWindow = nullptr;
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
    connect(m_soloGameView, &SoloGameWindow::onPauseClicked, this, &SoloGameController::showPauseWindow);
}

void SoloGameController::openMainMenu() {

    m_soloGameView->hide();
    m_mainMenuView->show();
    emit menuLauched();
}

void SoloGameController::showPauseWindow() {
    qDebug() << "Pause clicked!";

    if (!m_pauseWindow) {
        m_pauseWindow = new pausewindow(m_soloGameView);
    }

    m_pauseWindow->exec();
}






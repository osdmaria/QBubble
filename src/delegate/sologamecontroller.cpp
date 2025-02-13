#include "sologamecontroller.h"

SoloGameController::SoloGameController(SoloGameWindow *soloGameView,MainMenuWindow *mainMenuView, QObject *parent)
    : QObject{parent}, m_soloGameView{soloGameView}, m_mainMenuView{mainMenuView}
{
    m_scoreModel = new ScoreModel();
    m_containerModel = new ContainerModel();
    m_pauseWindow = nullptr;
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
    connect(m_soloGameView, &SoloGameWindow::onPauseClicked, this, &SoloGameController::showPauseWindow); // Connecter le bouton pause
}

void SoloGameController::openMainMenu() {

    m_soloGameView->hide();
    m_mainMenuView->show();
    emit menuLauched();
}

void SoloGameController::showPauseWindow() {
    qDebug() << "Pause clicked!";

    // Create pause window on demand, so there's no memory issue
    if (!m_pauseWindow) {
        m_pauseWindow = new pausewindow(m_soloGameView); // Use parent to avoid memory leaks
    }

    m_pauseWindow->exec(); // Show the pause window in modal mode
}







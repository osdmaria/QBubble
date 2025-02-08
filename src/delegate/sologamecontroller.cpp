#include "sologamecontroller.h"

SoloGameController::SoloGameController(SoloGameWindow *soloGameView, QObject *parent)
    : QObject{parent}, m_soloGameView{soloGameView}
{
    m_scoreModel = new ScoreModel();
    m_containerModel = new ContainerModel();

    connect(m_scoreModel, &ScoreModel::scoreChanged, this, &SoloGameController::updateScore);
}

SoloGameController::~SoloGameController(){
    delete m_scoreModel;
}


void SoloGameController::updateScore(int x)
{
    m_soloGameView->scoreWidget()->updateLabel(x);
}


#include "src/delegate/alliesgamecontroller.h"

AlliesGameController::AlliesGameController(AlliesGameWindow *alliesGameView, QObject *parent)
    : QObject{parent}, m_alliesGameView{alliesGameView}
{
    m_scoreModel = new ScoreModel();
    m_containerModel = new ContainerModel();

    connect(m_scoreModel, &ScoreModel::scoreChanged, this, &AlliesGameController::updateScore);
}

AlliesGameController::~AlliesGameController(){
    delete m_scoreModel;
}


void AlliesGameController::updateScore(int x)
{
    m_alliesGameView->scoreWidget()->updateLabel(x);
}

#include "enemiesgamecontroller.h"

EnemiesGameController::EnemiesGameController(EnemiesGameWindow *enemiesGameView, QObject *parent)
    : QObject{parent}, m_enemiesGameView{enemiesGameView}
{
    m_scoreModel = new ScoreModel();
    m_containerModel = new ContainerModel();

    connect(m_scoreModel, &ScoreModel::scoreChanged, this, &EnemiesGameController::updateScore);
}

EnemiesGameController::~EnemiesGameController(){
    delete m_scoreModel;
}


void EnemiesGameController::updateScore(int x)
{
    m_enemiesGameView->scoreWidget()->updateLabel(x);
}

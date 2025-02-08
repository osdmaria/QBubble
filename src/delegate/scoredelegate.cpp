#include "src/delegate/scoredelegate.h"

ScoreDelegate::ScoreDelegate(ScoreWidget *scoreWidget, ScoreModel *scoreModel, QObject *parent)
    : QObject{parent}, m_scoreWidget{scoreWidget}, m_scoreModel{scoreModel}
{

    connect(m_scoreModel, &ScoreModel::scoreChanged, this, &ScoreDelegate::updateScore);
}


void ScoreDelegate::updateScore(int x)
{

    if (m_scoreWidget) {
        m_scoreWidget->updateLabel(x);
    }
}

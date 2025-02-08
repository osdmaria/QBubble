#include "src/model/scoremodel.h"

ScoreModel::ScoreModel(QObject *parent)
    : QObject{parent}
{
    m_score = 0;
}

void ScoreModel::addPoints(int x){
    m_score += x;
    emit scoreChanged(m_score);
}

void ScoreModel::resetScore(){
    m_score = 0;
}

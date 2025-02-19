#include "src/model/scoremodel.h"

ScoreModel::ScoreModel(QObject *parent)
    : QObject{parent}
{
    m_score = 0;
}

void ScoreModel::calculScore(QVector<Bubble*> vec){
    int multiplier = 1;
    int size = vec.size();

    if(size>3)
        multiplier=2;
    else if (size > 4)
        multiplier = 3;
    else if (size > 6)
        multiplier = 4;

    int sum = 0;
    for(int i=0; i<vec.size();i++){
        sum += vec[i]->score();
    }

    sum *= multiplier;
    emit calculScoreHandled(vec);

    if(sum!=0)
        addPoints(sum);
}

void ScoreModel::addPoints(int x){
    m_score += x;
    emit scoreChanged(m_score);
}

void ScoreModel::resetScore(){
    m_score = 0;
}

#include "bubble.h"

Bubble::Bubble(QObject *parent)
    : QObject{parent}
{
    m_gridPosition.fill(-1);
}


bool Bubble::isColored(){return true;}
bool Bubble::isDestructible(){return true;}
bool Bubble::isExplosive(){return false;}

void Bubble::printType() {
    qDebug()<< "Bulle";
}

QString Bubble::type() const {return "Bulle";}


void Bubble::printPositions(){
    qDebug()<<"cartesian ("<<m_position.x()<<","<<m_position.y()
             <<") -- matrix2D ("<<m_gridPosition[0]<<","<<m_gridPosition[1]<<")";
}

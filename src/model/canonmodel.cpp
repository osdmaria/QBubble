#include "canonmodel.h"

CanonModel::CanonModel(QObject *parent) : QObject(parent), angle(90) {
}

CanonModel::~CanonModel() {
    delete m_currentBubble;
}

qreal CanonModel::getAngle() const {
    return angle;
}

void CanonModel::updateAngle(int direction) {
    if (direction == 1 && angle > 20) {
        angle -= 4; // Left arrow -> decrease angle
    } else if (direction == -1 && angle < 160) {
        angle += 4; // Right arrow -> increase angle
    }

    // Emit the new angle
    emit angleChanged(angle);
}

void CanonModel::loadBubble(Bubble *b){
    m_currentBubble = b;
    emit cannonLoaded();
}

void CanonModel::fire(){
    if(m_currentBubble){
        qDebug()<<"Cannoon fired"<<m_currentBubble->type();
        emit cannonFired(angle, m_currentBubble);
    } else {
        qDebug()<<"Cannon unloaded";
    }
}



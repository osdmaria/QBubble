#include "canonmodel.h"

CanonModel::CanonModel(QObject *parent) : QObject(parent), angle(90) {
}

CanonModel::~CanonModel() {
    // if(m_currentBubble)
    //     delete m_currentBubble;
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
        Bubble *tmp = m_currentBubble;
        emit cannonFired(angle, m_currentBubble);
        if(tmp==m_currentBubble)
            m_currentBubble = nullptr;
    } else {
        //m_currentBubble = nullptr;
        //qDebug()<<"Cannon unloaded";
    }
}


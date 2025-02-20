#include "canonmodel.h"

CanonModel::CanonModel(QObject *parent) : QObject(parent), angle(90) {
}

CanonModel::~CanonModel() {
    //qDebug()<<"last bubble is going to be deleted";
    //if(m_currentBubble)
    //    delete m_currentBubble;
    // else
    //     qDebug()<<"the is no bubble to delete";
    // qDebug()<<"last bubble deleted";

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
    //qDebug()<<"canon rechargé";
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


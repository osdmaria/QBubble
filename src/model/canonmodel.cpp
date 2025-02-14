#include "canonmodel.h"

CanonModel::CanonModel(QObject *parent) : QObject(parent), angle(90) {
    m_currentBubble = new ColoredBubble("lightblue");
}

CanonModel::~CanonModel() {
    delete m_currentBubble;
}

qreal CanonModel::getAngle() const {
    return angle;
}

void CanonModel::updateAngle(int direction) {
    if (direction == 1 && angle > 25) {
        angle -= 6; // Left arrow -> decrease angle
    } else if (direction == -1 && angle < 155) {
        angle += 6; // Right arrow -> increase angle
    }

    // Emit the new angle
    emit angleChanged(angle);
}

void CanonModel::loadBubble(Bubble *b){
    m_currentBubble = b;
    qDebug()<<"Le canon est rechargé";
}

void CanonModel::fire(){
    if(m_currentBubble){
        //handleFire
        qDebug()<<"Le canon tire";
        emit cannonFired(m_currentBubble);
        m_currentBubble = nullptr;
    }

}

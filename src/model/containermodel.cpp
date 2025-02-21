#include "containermodel.h"
#include "src/model/coloredbubble.h"
#include "src/model/explosivebubble.h"
#include "src/model/indestructiblebubble.h"

ContainerModel::ContainerModel(QObject *parent)
    : QObject{parent}
{
    m_container[0] =  nullptr;
    m_container[1] = nullptr;
    m_container[2] = nullptr;
}

ContainerModel::~ContainerModel() {
    for (int i = 0; i < 3; ++i) {
        delete m_container[i];
        m_container[i] = nullptr;
    }
}

Bubble *ContainerModel::popRight(){
    Bubble *toReturn = getBubbleAt(m_size-1);
    setNullAt(m_size-1);
    return toReturn;
}

Bubble *ContainerModel::popLeft(){
    Bubble *toReturn = getBubbleAt(0);
    setNullAt(0);
    return toReturn;
}

void ContainerModel::moveAllRight(){
    for(int i=m_size-1; i>0; i--){
        m_container[i] = m_container[i-1];
    }
}

void ContainerModel::moveAllLeft(){
    for(int i=0; i<m_size-1; i++){
        m_container[i] = m_container[i+1];
    }
}


Bubble *ContainerModel::addLeft(Bubble *b){
    Bubble *toReturn = popRight();
    moveAllRight();
    setBubbleAt(0,b);
    return toReturn;
}

Bubble *ContainerModel::addRight(Bubble *b){
    Bubble *toReturn = popLeft();
    moveAllLeft();
    setBubbleAt(m_size-1,b);
    return toReturn;
}

void ContainerModel::initContainer(QVector<Bubble*> bubbles){
    m_container[0] = bubbles[0];
    m_container[1] = bubbles[1];
    m_container[2] = bubbles[2];
    emit bubblesChanged();
}

void ContainerModel::fill(Bubble *b){
    Bubble *bubble = addLeft(b);
    if(bubble){
        emit transmitBubble(bubble);
        emit bubblesChanged();
    }

}

#include "containermodel.h"

ContainerModel::ContainerModel(QObject *parent)
    : QObject{parent}
{
}

ContainerModel::~ContainerModel() {}

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


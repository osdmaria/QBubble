#ifndef CANNONMODEL_H
#define CANNONMODEL_H

#include <QObject>

#include "src/model/bubble.h"

class CannonModel : public QObject
{
    Q_OBJECT
public:
    explicit CannonModel(QObject *parent = nullptr);
    ~CannonModel();
    void currentBubble(Bubble *bubble) {m_currentBubble = bubble;}
    Bubble *currentBubble(){return m_currentBubble;}
    void addRotation(float x){m_rotation += x;}
    void rotation(float x){m_rotation = x;}
    float rotation(){return m_rotation;}

signals:
    void cannonRotated();
    void cannonFired();
    
private:
    Bubble *m_currentBubble;
    float m_rotation;
    
};

#endif // CANNONMODEL_H

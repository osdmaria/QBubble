#ifndef CONTAINERMODEL_H
#define CONTAINERMODEL_H

#include <QObject>

#include "src/model/bubble.h"
class ContainerModel : public QObject
{
    Q_OBJECT
public:
    explicit ContainerModel(QObject *parent = nullptr);
    ~ContainerModel();

    //getters
    Bubble *getBubbleAt(int index){return m_container[index];}
    int size(){return m_size;}

    //setter
    void setBubbleAt(int index, Bubble *b) {m_container[index] = b;}
    void setNullAt(int index) {m_container[index] = nullptr;}

    //others
    Bubble *popRight();
    Bubble *popLeft();

    void moveAllRight();
    void moveAllLeft();

    Bubble *addLeft(Bubble *b);
    Bubble *addRight(Bubble *b);

    void initContainer(QVector<Bubble*> bubbles);

public slots:
    void fill(Bubble *b);

signals:
    void transmitBubble(Bubble *b);
    void bubblesChanged();

private:
    int m_size = 3;
    Bubble *m_container[3];

};

#endif // CONTAINERMODEL_H

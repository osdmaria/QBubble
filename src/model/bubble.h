#ifndef BUBBLE_H
#define BUBBLE_H

#include <QObject>
#include <QPointF>
#include <QDebug>

class Bubble : public QObject
{
    Q_OBJECT
    int m_scoreValue;
    QPoint m_position;
    QVector<int> m_gridPosition = QVector<int>(2);


public:
    explicit Bubble(QObject *parent = nullptr);
    virtual bool isColored();
    virtual bool isDestructible();
    virtual bool isExplosive();
    virtual QString type() const;

    QPoint position() const {return m_position;}
    void position(QPoint p){m_position = p;}
    QVector<int> gridPosition() const {return m_gridPosition;}
    void gridPosition(QVector<int> p){m_gridPosition = p;}

    void printPositions();
    virtual void printType()  = 0 ;

};

#endif // BUBBLE_H

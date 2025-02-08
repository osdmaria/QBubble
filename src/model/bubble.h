#ifndef BUBBLE_H
#define BUBBLE_H

#include <QObject>
#include <QPointF>

class Bubble : public QObject
{
    Q_OBJECT
    int m_scoreValue;
    bool m_isDestructible;
    QPointF m_position;


public:
    explicit Bubble(QObject *parent = nullptr);
    ~Bubble();

    QPointF position(){return m_position;}
    void position(QPointF p){m_position = p;}

signals:

private:

};

#endif // BUBBLE_H

#ifndef BUBBLE_H
#define BUBBLE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemAnimation>
#include <QPropertyAnimation>
#include <QTimer>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QRectF>
#include <QPixmap>
#include <QPointF>
#include <QTimeLine>
#include <QLabel>

class Bubble : public QGraphicsItem
{
    //Q_OBJECT
    //Q_PROPERTY(QPointF pos READ pos WRITE setPos)

    QPixmap m_bubbleImage;
    QPointF m_position;
    QPointF m_velocity;
    qreal m_radius ;
    int m_scoreValue;
    bool m_isDestructible;
    bool m_isAttached;

public:
    Bubble(const QString&, qreal);
    ~Bubble();

    //setters
    void setPosition(qreal posX, qreal posY);
    void setRadius(qreal r);

    //getters
    qreal getRadius() const { return m_radius; }
    QPointF getPosition(){return m_position;}
    QPixmap getBubbleImage(){return m_bubbleImage;}

    //others
    QGraphicsItemAnimation* animationLinearMovement(qreal xBegin, qreal yBegin, qreal xEnd, qreal yEnd, int animationTime);


protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // BUBBLE_H

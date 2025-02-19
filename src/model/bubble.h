#ifndef BUBBLE_H
#define BUBBLE_H


#include <QObject>
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
class Bubble : public QObject
{
    Q_OBJECT

private:
    QColor m_color;
    int m_scoreValue = 10;
    QPointF m_position;
    bool m_isDestructible;
    QVector<int> m_gridPosition = QVector<int>(2);


public:
    explicit Bubble(QObject *parent = nullptr);
    ~Bubble();
    virtual bool isColored();
    virtual bool isDestructible();
    virtual bool isExplosive();
    virtual QString type() const;

    QPointF position() const {return m_position;}
    void position(QPointF p){m_position = p;}
    QVector<int> gridPosition() const {return m_gridPosition;}
    void gridPosition(QVector<int> p){m_gridPosition = p;}
    int score(){return m_scoreValue;}

    void printPositions();
    virtual void printType()  = 0 ;


    QPointF pos() const;
    void setPos(const QPointF& pos);

signals:


};

#endif // BUBBLE_H

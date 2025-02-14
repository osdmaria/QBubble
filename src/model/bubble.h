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
    Q_PROPERTY(QPointF pos READ pos WRITE setPos NOTIFY posChanged)

private:
    QColor m_color;
    int m_scoreValue;
    QPointF m_position;
    bool m_isDestructible;
    QVector<int> m_gridPosition = QVector<int>(2);


public:
    explicit Bubble(QObject *parent = nullptr);
    virtual bool isColored();
    virtual bool isDestructible();
    virtual bool isExplosive();
    virtual QString type() const;

    QPointF position() const {return m_position;}
    void position(QPointF p){m_position = p;}
    QVector<int> gridPosition() const {return m_gridPosition;}
    void gridPosition(QVector<int> p){m_gridPosition = p;}

    void printPositions();
    virtual void printType()  = 0 ;

    void setColor(const QColor &c) {
        if (m_color != c) {
            m_color = c;
            emit colorChanged(m_color);
        }
    }

    void setScoreValue(int value) {
        if (m_scoreValue != value) {
            m_scoreValue = value;
            emit scoreValueChanged(m_scoreValue);
        }
    }

    void setDestructible(bool destructible) {
        if (m_isDestructible != destructible) {
            m_isDestructible = destructible;
            emit destructibleChanged(m_isDestructible);
        }
    }
    ~Bubble();
    QPointF pos() const;
    void setPos(const QPointF& pos);

signals:
    void popped();
    void positionChanged(QPointF newPosition, bool offset);
    void colorChanged(QColor newColor);

    void scoreValueChanged(int newScoreValue);
    void destructibleChanged(bool newDestructible);
    void posChanged();

};

#endif // BUBBLE_H

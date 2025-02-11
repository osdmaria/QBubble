#ifndef BUBBLE_H
#define BUBBLE_H

#include <QObject>
#include <QColor>
#include <QPointF>
#include <QDebug>

class Bubble : public QObject
{
    Q_OBJECT

private:
    QColor m_color;
    int m_scoreValue;
    bool m_isDestructible;
    QPointF m_position;

public:
    explicit Bubble(QColor color, int scoreValue, bool isDestructible, QPointF position, QObject *parent = nullptr);
    explicit Bubble(QColor color, QPointF position, QObject *parent = nullptr);
    ~Bubble();

    // Getters
    QPointF position() const { return m_position; }
    QColor color() const { return m_color; }
    int scoreValue() const { return m_scoreValue; }
    bool isDestructible() const { return m_isDestructible; }

    // Setters (Emit Signals)
    void setPosition(const QPointF &p, bool offset) {
        if (m_position != p) {
            m_position = p;
            // qDebug() << "Will emit positionChanged()";
            emit positionChanged(m_position, offset);
        }
    }

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

signals:
    void popped();
    void positionChanged(QPointF newPosition, bool offset);
    void colorChanged(QColor newColor);

    void scoreValueChanged(int newScoreValue);
    void destructibleChanged(bool newDestructible);
};

#endif // BUBBLE_H

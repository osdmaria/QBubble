
#include "bubble.h"

Bubble::Bubble(QColor color, int scoreValue, bool isDestructible, QPointF position, QObject *parent)
    : QObject{parent},
    m_color{color},
    m_scoreValue{scoreValue},
    m_isDestructible{isDestructible},
    m_position{position} {}

Bubble::Bubble(QColor color, QPointF position, QObject *parent)
    : QObject{parent},
    m_color{color},
    m_scoreValue{1},
    m_isDestructible{true},
    m_position{position} {}

Bubble::~Bubble() {}

QPointF Bubble::pos() const {
    return m_position;
}

void Bubble::setPos(const QPointF& pos) {
    if (m_position != pos) {
        m_position = pos;
        emit posChanged();
    }
}



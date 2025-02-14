#include "coloredbubble.h"
#include <QDebug>
ColoredBubble::ColoredBubble(const QString& color, QObject *parent)
    : Bubble(parent), m_color(color)
{
}


bool ColoredBubble::isColored() { return true; }
bool ColoredBubble::isDestructible() { return true; }
bool ColoredBubble::isExplosive() { return false; }

void ColoredBubble::printType() {
    qDebug()<<m_color;
}

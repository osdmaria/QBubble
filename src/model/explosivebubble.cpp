#include "explosivebubble.h"

ExplosiveBubble::ExplosiveBubble(int radiusExplosion, QObject *parent)
    : Bubble(parent), m_explosionRadius{radiusExplosion}
{
}

bool ExplosiveBubble::isColored() { return false; }
bool ExplosiveBubble::isDestructible() { return true; }
bool ExplosiveBubble::isExplosive() { return true; }

void ExplosiveBubble::printType() {
    qDebug()<<"Explosive";
}

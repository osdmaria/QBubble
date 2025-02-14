#include "indestructiblebubble.h"

IndestructibleBubble::IndestructibleBubble(QObject *parent)
    : Bubble(parent)
{}
bool IndestructibleBubble::isColored() { return false; }
bool IndestructibleBubble::isDestructible() { return false; }
bool IndestructibleBubble::isExplosive() { return false; }

void IndestructibleBubble::printType() {
    qDebug()<<"Indestructible";
}

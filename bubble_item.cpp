#include "bubble_item.h"
#include <QBrush>

BubbleItem::BubbleItem(QColor color, int radius, QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent), m_color(color) {
    // Set the bounding box for the bubble (a circle with diameter = 2 * radius)
    setRect(-radius, -radius, 2 * radius, 2 * radius);

    // Set the color of the bubble
    setBrush(QBrush(m_color));

    // Make the bubble's center (0,0) to match its position
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
}

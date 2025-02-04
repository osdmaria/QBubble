#ifndef BUBBLEITEM_H
#define BUBBLEITEM_H

#include <QGraphicsEllipseItem>
#include <QColor>

class BubbleItem : public QGraphicsEllipseItem {
public:
    BubbleItem(QColor color, int radius, QGraphicsItem *parent = nullptr);

    QColor getColor() const { return m_color; }

private:
    QColor m_color;
};

#endif // BUBBLEITEM_H

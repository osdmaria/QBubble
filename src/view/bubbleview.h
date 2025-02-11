
#ifndef BUBBLEVIEW_H
#define BUBBLEVIEW_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QObject>  // Add this!
#include "src/model/bubble.h"

class BubbleView : public QObject, public QGraphicsItem {  // Add QObject as a parent class
    Q_OBJECT  // Add this!

public:
    explicit BubbleView(Bubble* bubble, int radius, bool offset, QGraphicsItem *parent = nullptr);
    ~BubbleView() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QPixmap getImage() const { return m_bubbleImage; }
    static QPixmap loadImageByColor(const QColor &color); // Static method to get image by color

private slots:
    void updatePosition(QPointF newPos, bool offset);
    void updateColor(QColor newColor);
    void popped();

private:
    Bubble* m_bubble;
    QPixmap m_bubbleImage;
    int m_radius;
    bool m_offset;
};

#endif // BUBBLEVIEW_H

#ifndef BUBBLEVIEW_H
#define BUBBLEVIEW_H

#include <QGraphicsItem>
#include <QPainter>

#include "bubbleview.h"
#include "src/model/bubble.h"

class BubbleView : public QGraphicsItem {
public:
    BubbleView(const QPixmap &bubbleImage, QGraphicsItem *parent = nullptr);
    ~BubbleView();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPixmap getImage(){return m_bubbleImage;}
private:
    QPixmap m_bubbleImage;

};

#endif // BUBBLEVIEW_H


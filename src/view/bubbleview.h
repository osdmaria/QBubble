#ifndef BUBBLEVIEW_H
#define BUBBLEVIEW_H

#include <QGraphicsItem>
#include <QPainter>

#include "src/model/explosivebubble.h"
#include "src/model/coloredbubble.h"
#include "src/model/indestructiblebubble.h"

class BubbleView : public QGraphicsItem {
public:
    BubbleView(const QString bubbleType, int radius, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QPixmap getImage(){return m_bubbleImage;}
    int radius(){return m_radius;}
    void radius(int r){m_radius = r;}


    void loadImage(const QString s);
    QPixmap getImage() const { return m_bubbleImage; }
    static QPixmap loadImageByColor(const QColor &color); // Static method to get image by color
    QGraphicsItemAnimation* animationLinearMovement(qreal xBegin, qreal yBegin, qreal xEnd, qreal yEnd, int animationTime);


private:
    QPixmap m_bubbleImage;
    int m_radius;

};

#endif // BUBBLEVIEW_H

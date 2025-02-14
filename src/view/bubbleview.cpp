#include "bubbleview.h"

BubbleView::BubbleView(const QString bubbleType, int radius, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_radius(radius) {

    int m_radius = radius;
    loadImage(bubbleType);
    if (!m_bubbleImage.isNull()) {
        m_bubbleImage = m_bubbleImage.scaled(m_radius, m_radius, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    } else {
        qWarning() << "Image is null";
    }
}


QRectF BubbleView::boundingRect() const {
    return QRectF(0, 0, m_bubbleImage.width(), m_bubbleImage.height());
}

void BubbleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (!m_bubbleImage.isNull()) {
        painter->drawPixmap(0, 0, m_bubbleImage);
    }
}

void BubbleView::loadImage(const QString s){
    if(s.compare("lightblue")==0){
        m_bubbleImage = QPixmap(":/images/bubble_lightblue");
    }
    if(s.compare("bordeaux")==0){
        m_bubbleImage = QPixmap(":/images/bubble_bordeaux");
    }
    if(s.compare("brown")==0){
        m_bubbleImage = QPixmap(":/images/bubble_brown");
    }
    if(s.compare("green")==0){
        m_bubbleImage = QPixmap(":/images/bubble_green");
    }
    if(s.compare("explosive")==0){
        m_bubbleImage = QPixmap(":/images/bubble_explosive");
    }
    if(s.compare("indestructible")==0){
        m_bubbleImage = QPixmap(":/images/bubble_indestructible");
    }
}

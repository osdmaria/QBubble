#include "bubbleview.h"

BubbleView::BubbleView(const QPixmap &bubbleImage,QGraphicsItem *parent)
    : QGraphicsItem(parent), m_bubbleImage(bubbleImage){

    int radius = 40;
    if (!m_bubbleImage.isNull()) {
        m_bubbleImage = m_bubbleImage.scaled(radius, radius, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    } else {
        qWarning() << "Image is null";
    }
}

BubbleView::~BubbleView() {}

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

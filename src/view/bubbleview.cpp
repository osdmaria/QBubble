#include "bubbleview.h"
#include <QDebug>

BubbleView::BubbleView(Bubble* bubble, int radius,  bool offset, QGraphicsItem *parent)
    : QGraphicsItem(parent),
    m_bubble(bubble),
    m_radius(radius),
    m_offset(offset),
    m_bubbleImage() {
    // si offset = true : decalage à gauche
    if (m_bubble) {
        connect(m_bubble, &Bubble::positionChanged, this, &BubbleView::updatePosition);
        connect(m_bubble, &Bubble::colorChanged, this, &BubbleView::updateColor);
        connect(m_bubble, &Bubble::popped, this, &BubbleView::popped);
        m_bubbleImage = loadImageByColor(m_bubble->color());
        m_bubbleImage = m_bubbleImage.scaled(m_radius, m_radius, Qt::KeepAspectRatio, Qt::SmoothTransformation);


        int row = bubble->position().x();
        int col = bubble->position().y();
        int x = col * radius*2 + (offset ? -radius/ 2 : radius/ 2);
        int y = row * radius*2 ;

        setPos(x,y); // Initialize position
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

QPixmap BubbleView::loadImageByColor(const QColor &color) {
    QString imagePath;

    if (color == QColor(128,0,32)) {
        imagePath = ":/images/bubble_bordeaux.png";
    } else if (color == QColor(105,105,25)) {
        imagePath = ":/images/bubble_brown.png";
    } else if (color == Qt::green) {
        imagePath = ":/images/bubble_green.png";
    } else if (color == QColor(176,213,230)) {
        imagePath = ":/images/bubble_lightblue.png";
    }

    else {
        imagePath = ":/images/bubble_bordeaux.png"; // Default color (purple)
    }

    QPixmap pixmap;
    if (!pixmap.load(imagePath)) {
        qWarning() << "BubbleView: Failed to load image" << imagePath;
    }
    return pixmap;
}


void BubbleView::updatePosition(QPointF newPos, bool offset){

    int x = newPos.y() * m_radius*2 + (offset ? -m_radius/ 2 : m_radius/ 2);
    int y = newPos.x() * m_radius*2 ;

    setPos(x,y);
}

void BubbleView::updateColor(QColor newColor){
    m_bubbleImage = loadImageByColor(newColor);
    m_bubbleImage = m_bubbleImage.scaled(m_radius, m_radius, Qt::KeepAspectRatio, Qt::SmoothTransformation);

}


void BubbleView::popped(){
    qDebug() << "Add animation of bubble popped";
}


QGraphicsItemAnimation* BubbleView::animationLinearMovement(qreal xBegin, qreal yBegin, qreal xEnd, qreal yEnd, int animationTime) {
    QTimeLine* timer = new QTimeLine(animationTime);
    QGraphicsItemAnimation* animation = new QGraphicsItemAnimation;
    int maxFrameRange = 200;
    timer->setFrameRange(0, maxFrameRange);

    qreal distanceX = (xEnd - xBegin);
    qreal distanceY = (yEnd - yBegin);

    for (int i = 0; i <= maxFrameRange; ++i) {
        qreal step = static_cast<qreal>(i) / maxFrameRange;
        qreal posX = xBegin + distanceX * step;
        qreal posY = yBegin + distanceY * step;
        animation->setPosAt(step, QPointF(posX, posY));
    }

    animation->setItem(this);
    animation->setTimeLine(timer);
    timer->start();

    return animation;
}

#include "bubble.h"

#include <QPushButton>

Bubble::Bubble(const QString &filename, qreal r)
{
    if (!filename.isEmpty()) {
        bool loaded = m_bubbleImage.load(filename);
        if (!loaded) {
            qWarning() << "Failed to load image:" << filename;
        }
    }

    m_radius = r;
    if (!m_bubbleImage.isNull()) {
        m_bubbleImage = m_bubbleImage.scaled(2 * m_radius, 2 * m_radius, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    } else {
        qWarning() << "Image is null, setting default color or image instead";
    }
}

Bubble::~Bubble() {}

void Bubble::setRadius(qreal r)
{
    if (m_radius != r) {
        m_radius = r;
        prepareGeometryChange();  // Notifie la scène
    }
}

void Bubble::setPosition(qreal posX, qreal posY) {
    m_position = QPointF(posX, posY);
    setPos(m_position); // This is critical to update the position in the scene
}


QRectF Bubble::boundingRect() const
{
    return QRectF(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
}

void Bubble::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (!m_bubbleImage.isNull()) {
        QRectF targetRect(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
        painter->drawPixmap(targetRect.toRect(), m_bubbleImage);
    }
}

QGraphicsItemAnimation* Bubble::animationLinearMovement(qreal xBegin, qreal yBegin, qreal xEnd, qreal yEnd, int animationTime){
    QTimeLine *timer = new QTimeLine(animationTime);
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    int maxFrameRange = 200;
    timer->setFrameRange(0, maxFrameRange);

    qreal distanceX = (xEnd - xBegin);
    qreal distanceY = (yEnd - yBegin);

    for (int i = 0; i <= maxFrameRange; ++i) {
        qreal step = static_cast<qreal>(i) / maxFrameRange;
        qreal posX = xBegin + distanceX * step;
        qreal posY = yBegin + distanceY * step;
        animation->setPosAt(step, QPointF(posX,posY));
    }

    animation->setItem(this);
    animation->setTimeLine(timer);
    timer->start();

    return animation;
}

#include "canonwidget.h"
#include "qpainterpath.h"
#include <QLabel>
#include <QHBoxLayout>
CanonWidget::CanonWidget(int bubbleRadius, int radius, int startX, int startY, QWidget *parent)
    : QWidget(parent), m_radius(radius), startX(startX), startY(startY)
{
    if (radius <= 0) {
        qDebug() << "Error: Invalid radius!";
        return;
    }

    m_spotBubble = new QLabel(this);
    m_spotBubble->setFixedSize(bubbleRadius, bubbleRadius);
    //m_layout = new QHBoxLayout(this);
    //m_layout->addWidget(m_spotBubble, 0, Qt::AlignCenter);
    //setLayout(m_layout);
    m_spotBubble->move(65,100);

    setFocusPolicy(Qt::StrongFocus); // Make the widget focusable
    setFocus();

    // Set the size of the widget
    setFixedSize(250, 250);
}

CanonWidget::~CanonWidget() {}

void CanonWidget::updateBubble(BubbleView *b){
    if(m_bubble){
        //m_layout->removeWidget(m_spotBubble);
        m_spotBubble->clear();
        m_bubble = nullptr;
    }
    m_bubble = b;
    if(b){
        m_spotBubble->setPixmap(b->getImage());
    }

}

void CanonWidget::onAngleChanged(qreal newAngle) {
    m_currentAngle = newAngle;
    update();
}

void CanonWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        emit updateAngle(-1);
    }
    else if (event->key() == Qt::Key_Right) {
        emit updateAngle(1);
    }
    else if (event->key() == Qt::Key_Space) {
        emit shootSignal();
    }
}

void CanonWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Pen for drawing the line with rounded edges and light brown color
    pen.setColor(QColor(181, 101, 29)); // Light brown color (RGB)
    pen.setWidth(6);
    pen.setCapStyle(Qt::RoundCap);  // Rounded edges for the line
    painter.setPen(pen);

    // Calculate the end point of the cannon line based on the angle
    qreal length = m_radius * 3;
    qreal endX = startX + length * qCos(qDegreesToRadians(m_currentAngle));
    qreal endY = startY - length * qSin(qDegreesToRadians(m_currentAngle)); // Negative Y for upward direction

    // Draw the line
    painter.drawLine(startX, startY, endX, endY);

    // Add the arrowhead at the end of the line
    QPainterPath path;
    path.moveTo(endX, endY);  // Start at the end of the line
    // Draw the arrow (a triangle)
    qreal arrowSize = 10; // Size of the arrow
    qreal angleRad = qDegreesToRadians(-m_currentAngle);

    // Calculate the two points for the sides of the arrow
    QPointF p1(endX - arrowSize * qCos(angleRad - M_PI_4), endY - arrowSize * qSin(angleRad - M_PI_4));
    QPointF p2(endX - arrowSize * qCos(angleRad + M_PI_4), endY - arrowSize * qSin(angleRad + M_PI_4));

    path.lineTo(p1);
    path.moveTo(endX, endY);
    path.lineTo(p2);

    // Draw the arrowhead
    painter.setBrush(QBrush(QColor(181, 101, 29)));  // Same light brown color for the arrowhead
    painter.drawPath(path);
}

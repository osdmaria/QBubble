#include "canonwidget.h"
#include "qpainterpath.h"
#include <QPainter>
#include <QDebug>

CanonWidget::CanonWidget(QWidget *parent, int radius, int startX, int startY)
    : QWidget(parent), angle(90), m_radius(radius), startX(startX), startY(startY)
{
    if (radius <= 0) {
        qDebug() << "Error: Invalid radius!";
        return;
    }

    setFocusPolicy(Qt::StrongFocus); // Make the widget focusable
    setFocus();

    // Set the size of the widget
    setFixedSize(250, 250);
}

CanonWidget::~CanonWidget() {}

qreal CanonWidget::getAngle() const {
    return angle;
}

void CanonWidget::updateAngle(int direction) {
    if (direction == 1 && angle > 25) {
        angle -= 6; // Left arrow -> decrease angle
    } else if (direction == -1 && angle < 155) {
        angle += 6; // Right arrow -> increase angle
    }

    // Update the widget (request paint event)
    update();
}

void CanonWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        updateAngle(-1); // Left arrow
        qDebug() << "leftoo";
        qDebug() << "Current angle" << angle;
    }
    else if (event->key() == Qt::Key_Right) {
        updateAngle(1); // Right arrow
        qDebug() << "rightoo";
        qDebug() << "Current angle" << angle;
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
    qreal endX = startX + length * qCos(qDegreesToRadians(angle));
    qreal endY = startY - length * qSin(qDegreesToRadians(angle)); // Negative Y for upward direction

    // Draw the line
    painter.drawLine(startX, startY, endX, endY);

    // Add the arrowhead at the end of the line
    QPainterPath path;
    path.moveTo(endX, endY);  // Start at the end of the line
    // Draw the arrow (a triangle)
    qreal arrowSize = 10; // Size of the arrow
    qreal angleRad = qDegreesToRadians(-angle);

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


QSize CanonWidget::sizeHint() const {
    return QSize(m_radius * 2, m_radius * 2);
}

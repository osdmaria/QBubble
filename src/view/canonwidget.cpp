#include "canonwidget.h"
#include "qpainterpath.h"

CanonWidget::CanonWidget(QWidget *parent, CanonModel *model, int radius, int startX, int startY)
    : QWidget(parent), m_model(model), m_radius(radius), startX(startX), startY(startY)
{
    if (radius <= 0) {
        qDebug() << "Error: Invalid radius!";
        return;
    }

    setFocusPolicy(Qt::StrongFocus); // Make the widget focusable
    setFocus();

    // Set the size of the widget
    setFixedSize(250, 250);
    setModel(model);
}

CanonWidget::~CanonWidget() {}

void CanonWidget::setModel(CanonModel *model) {
    this->m_model = model;

    // Connect the model's signals to the widget's slots
    connect(model, &CanonModel::angleChanged, this, &CanonWidget::onAngleChanged);
}

void CanonWidget::onAngleChanged(qreal newAngle) {
    // Update the UI when the angle changes
    update();
}

void CanonWidget::keyPressEvent(QKeyEvent *event) {
    if (!m_model) return; // Ensure the model is set

    if (event->key() == Qt::Key_Left) {
        m_model->updateAngle(-1); // Left arrow -> decrease angle
        qDebug() << "Left arrow pressed. Current angle:" << m_model->getAngle();
    }
    else if (event->key() == Qt::Key_Right) {
        m_model->updateAngle(1); // Right arrow -> increase angle
        qDebug() << "Right arrow pressed. Current angle:" << m_model->getAngle();
    }
    else if (event->key() == Qt::Key_Space) {
        // Emit the bubbleShot signal with the current angle
        emit m_model->BubbleShoot(static_cast<int>(m_model->getAngle()));
        qDebug() << "Spacebar pressed! Angle:" << m_model->getAngle();
    }
}

void CanonWidget::paintEvent(QPaintEvent *event) {
    if (!m_model) return; // Ensure the model is set

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Pen for drawing the line with rounded edges and light brown color
    pen.setColor(QColor(181, 101, 29)); // Light brown color (RGB)
    pen.setWidth(6);
    pen.setCapStyle(Qt::RoundCap);  // Rounded edges for the line
    painter.setPen(pen);

    // Calculate the end point of the cannon line based on the angle
    qreal length = m_radius * 3;
    qreal endX = startX + length * qCos(qDegreesToRadians(m_model->getAngle()));
    qreal endY = startY - length * qSin(qDegreesToRadians(m_model->getAngle())); // Negative Y for upward direction

    // Draw the line
    painter.drawLine(startX, startY, endX, endY);

    // Add the arrowhead at the end of the line
    QPainterPath path;
    path.moveTo(endX, endY);  // Start at the end of the line
    // Draw the arrow (a triangle)
    qreal arrowSize = 10; // Size of the arrow
    qreal angleRad = qDegreesToRadians(-m_model->getAngle());

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


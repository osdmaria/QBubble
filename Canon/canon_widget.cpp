#include "canon_widget.h"

CanonWidget::CanonWidget(QWidget *parent)
    : QWidget(parent), cannonImage(":/image/canon3.png"), rotationAngle(90.0)
{
    setMouseTracking(true);
    //QVBoxLayout *layout = new QVBoxLayout(this);
    // Add widgets like QLabel, QGraphicsView, or QFrame to represent the cannon
    //setLayout(layout);
    if (!cannonImage.isNull()) {
        // Set the widget size according to the image size
        setFixedSize(300, 400);
    }
}

CanonWidget::~CanonWidget() {}

void CanonWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    if (!cannonImage.isNull()) {
        // Draw the cannon image at the center-bottom of the widget
        // Translate the coordinate system to the center of the widget (center of the image)
        painter.translate(width() / 2, height() / 2);

        // Rotate the cannon according to the angle calculated from the mouse pointer
        painter.rotate(rotationAngle);

        // Draw the rotated cannon image with the rotation center at the center of the image
        painter.drawPixmap(-cannonImage.width() / 2, -cannonImage.height() / 2, cannonImage);
        qDebug() << "image est rotation";
    }else{
        qDebug() << "image est null";
    }
}

void CanonWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // When the mouse is pressed, emit the fireBubble signal
        QPointF start = this->rect().center(); // Start position of the bubble (cannon's center)
        QPointF end = calculateFireEndPosition(); // Calculate the end position (where the bubble will go)
        emit fireBubble(start, end); // Emit signal to QML or another part of the game logic
    }
}

void CanonWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPointF cannonCenter = this->rect().center();  // The center of the cannon
    QPointF mousePos = event->pos();

    // Calculate the angle between the cannon's center and the mouse pointer position
    qreal dx = mousePos.x() - cannonCenter.x();
    qreal dy = mousePos.y() - cannonCenter.y(); // Invert dy so that the Y-axis goes upward

    // Calculate the angle in radians
    qreal angle = qAtan2(dy, dx); // Use atan2 to calculate the precise angle in both directions

    // Convert from radians to degrees (0-360 degrees)
    rotationAngle = angle * 180 / M_PI; // To keep the rotation angle in the range from -180 to 180 degrees
    if (rotationAngle < 0) {
        rotationAngle += 360; // Ensure the rotation angle stays within the range of 0-360 degrees
    }

    // Update the widget to redraw the cannon with the new angle
    update();
}

QPointF CanonWidget::calculateFireEndPosition()
{
    // For simplicity, we just fire straight up; modify this based on the angle of the cannon
    return QPointF(this->rect().center().x(), 0); // End position above the cannon
}

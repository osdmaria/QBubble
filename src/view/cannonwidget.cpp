#include "cannonwidget.h"

CannonWidget::CannonWidget( QWidget *parent)
    : QWidget{parent}
{
    m_cannonImage = QPixmap(":/images/canon3.png");
    setFixedSize(150, 150);
}

CannonWidget::~CannonWidget() {}

void CannonWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    if (!m_cannonImage.isNull()) {
        painter.translate(width() / 2, height() / 2);
        painter.drawPixmap(-m_cannonImage.width() / 2, -m_cannonImage.height() / 2, m_cannonImage);
    }else{
        qDebug() << "image est null";
    }
}



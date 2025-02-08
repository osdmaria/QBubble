#include "containerwidget.h"
#include "src/view/bubbleview.h"

ContainerWidget::ContainerWidget(QWidget *parent)
    : QWidget{parent}
{
    m_containerBackground = QPixmap(":/images/frame.png");
    if (m_containerBackground.isNull()) {
        qWarning() << "Failed to load background image!";
    }

    m_spotBubble1 = new QLabel(this);
    m_spotBubble2 = new QLabel(this);
    m_spotBubble3 = new QLabel(this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_spotBubble1, 0, Qt::AlignCenter);
    layout->addWidget(m_spotBubble2, 0, Qt::AlignCenter);
    layout->addWidget(m_spotBubble3, 0, Qt::AlignCenter);

    QPixmap test1(":/images/bubble_bordeaux");
    test1 = test1.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    m_spotBubble1->setPixmap(test1);
    m_spotBubble2->setPixmap(test1);
    m_spotBubble3->setPixmap(test1);


    setLayout(layout);
    setFixedSize(300, 300);
}


void ContainerWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), m_containerBackground);
}

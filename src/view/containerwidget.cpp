#include "containerwidget.h"
#include "src/view/bubbleview.h"

ContainerWidget::ContainerWidget(QWidget *parent)
    : QWidget{parent}
{
    // m_containerBackground = QPixmap(":/images/frame.png");
    // if (m_containerBackground.isNull()) {
    //     qWarning() << "Failed to load background image!";
    // }

    m_spotBubble1 = new QLabel(this);
    m_spotBubble2 = new QLabel(this);
    m_spotBubble3 = new QLabel(this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_spotBubble1, 0, Qt::AlignCenter);
    layout->addWidget(m_spotBubble2, 0, Qt::AlignCenter);
    layout->addWidget(m_spotBubble3, 0, Qt::AlignCenter);

    QPixmap test1(":/images/bubble_explosive");
    QPixmap test2(":/images/bubble_indestructible");
    QPixmap test3(":/images/bubble_lightblue");
    test1 = test1.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    test2 = test2.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    test3 = test3.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    m_spotBubble1->setPixmap(test1);
    m_spotBubble2->setPixmap(test2);
    m_spotBubble3->setPixmap(test3);


    setLayout(layout);
    setFixedSize(300, 300);
}


void ContainerWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), m_containerBackground);
}

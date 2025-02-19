#include "containerwidget.h"
#include "src/view/bubbleview.h"

ContainerWidget::ContainerWidget(int bubbleRadius, QWidget *parent)
    : QWidget{parent}
{
    m_spotBubble1 = new QLabel(this);
    m_spotBubble2 = new QLabel(this);
    m_spotBubble3 = new QLabel(this);

    m_spotBubble1->setFixedSize(bubbleRadius, bubbleRadius);
    m_spotBubble2->setFixedSize(bubbleRadius, bubbleRadius);
    m_spotBubble3->setFixedSize(bubbleRadius, bubbleRadius);

    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(m_spotBubble1, 0, Qt::AlignCenter);
    m_layout->addWidget(m_spotBubble2, 0, Qt::AlignCenter);
    m_layout->addWidget(m_spotBubble3, 0, Qt::AlignCenter);

    setLayout(m_layout);
    setFixedSize(300, 300);
}

void ContainerWidget::deletePrevious() {
    if (m_bubble1) {
        m_layout->removeWidget(m_spotBubble1);
        m_spotBubble1->clear();
        m_bubble1 = nullptr;
    }
    if (m_bubble2) {
        m_layout->removeWidget(m_spotBubble2);
        m_spotBubble2->clear();
        m_bubble2 = nullptr;
    }
    if (m_bubble3) {
        m_layout->removeWidget(m_spotBubble3);
        m_spotBubble3->clear();
        m_bubble3 = nullptr;
    }
}


void ContainerWidget::updateView(BubbleView *b1, BubbleView *b2, BubbleView *b3) {
    deletePrevious();

    m_bubble1 = b1;
    m_bubble2 = b2;
    m_bubble3 = b3;

    if (b1)
        m_spotBubble1->setPixmap(b1->getImage());
    if (b2)
        m_spotBubble2->setPixmap(b2->getImage());
    if (b3)
        m_spotBubble3->setPixmap(b3->getImage());
}



void ContainerWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), m_containerBackground);
}

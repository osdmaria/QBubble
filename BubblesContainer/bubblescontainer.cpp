#include "bubblescontainer.h"

BubblesContainer::BubblesContainer(QWidget *parent)
    : QWidget(parent), m_containerBackground(":/images/frame.png")
{
    setupUi(this);
    m_layout = new QHBoxLayout(this);
    initLayout();

    setMaximumSize(200,50);

    //bulles de test
    Bubble *b1 = new Bubble(":/images/bubble_blue.png",30);
    Bubble *b2 = new Bubble(":/images/bubble_red.png",30);
    Bubble *b3 = new Bubble(":/images/bubble_purple.png",30);
    Bubble *b4 = new Bubble(":/images/bubble_yellow.png",30);

    setBubbleAt(0,b1);
    setBubbleAt(1,b2);
    setBubbleAt(2,b3);

    addLeft(b4);


    updateLayout();
}

BubblesContainer::~BubblesContainer() {}

void BubblesContainer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), m_containerBackground);
}

void BubblesContainer::initLayout(){
    QLabel *label1 = new QLabel(this);
    QLabel *label2 = new QLabel(this);
    QLabel *label3 = new QLabel(this);

    m_layout->addWidget(label1,0,Qt::AlignCenter);
    m_layout->addWidget(label2,0,Qt::AlignCenter);
    m_layout->addWidget(label3,0,Qt::AlignCenter);

    setLayout(m_layout);
}

void BubblesContainer::updateLayout(){
    for(int i=0; i<m_size;i++){
        if(m_container[i]!=nullptr){
            QLabel *label = qobject_cast<QLabel *>(m_layout->itemAt(i)->widget());
            label->setPixmap(m_container[i]->getBubbleImage());
        }
    }
}

Bubble *BubblesContainer::popRight(){
    Bubble *toReturn = getBubbleAt(m_size-1);
    setNullAt(m_size-1);
    return toReturn;
}

Bubble *BubblesContainer::popLeft(){
    Bubble *toReturn = getBubbleAt(0);
    setNullAt(0);
    return toReturn;
}

void BubblesContainer::moveAllRight(){
    for(int i=m_size-1; i>0; i--){
        m_container[i] = m_container[i-1];
    }
}

void BubblesContainer::moveAllLeft(){
    for(int i=0; i<m_size-1; i++){
        m_container[i] = m_container[i+1];
    }
}


Bubble *BubblesContainer::addLeft(Bubble *b){
    Bubble *toReturn = popRight();
    moveAllRight();
    setBubbleAt(0,b);
    updateLayout();
    return toReturn;
}

Bubble *BubblesContainer::addRight(Bubble *b){
    Bubble *toReturn = popLeft();
    moveAllLeft();
    setBubbleAt(m_size-1,b);
    updateLayout();
    return toReturn;
}



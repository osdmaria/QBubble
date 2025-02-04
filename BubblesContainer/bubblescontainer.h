#ifndef BUBBLESCONTAINER_H
#define BUBBLESCONTAINER_H

#include "ui_bubblescontainer.h"
#include "bubble.h"

#include <QWidget>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QPalette>
#include <QHBoxLayout>

class BubblesContainer : public QWidget, private Ui::BubblesContainer
{
    Q_OBJECT
    int m_size = 3;
    Bubble *m_container[3];
    QHBoxLayout *m_layout;
    QPixmap m_containerBackground;


public:
    BubblesContainer(QWidget *parent = nullptr);
    ~BubblesContainer();

    //getters
    Bubble *getBubbleAt(int index){return m_container[index];}
    int size(){return m_size;}

    //setter
    void setBubbleAt(int index, Bubble *b) {m_container[index] = b;}
    void setNullAt(int index) {m_container[index] = nullptr;}

    //others
    void initLayout();
    void updateLayout();


    Bubble *popRight();
    Bubble *popLeft();

    void moveAllRight();
    void moveAllLeft();

    Bubble *addLeft(Bubble *b);
    Bubble *addRight(Bubble *b);




protected:
    void paintEvent(QPaintEvent *event) override;
};
#endif // BUBBLESCONTAINER_H


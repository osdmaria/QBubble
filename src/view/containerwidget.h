#ifndef CONTAINERWIDGET_H
#define CONTAINERWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>

#include "bubbleview.h"

class ContainerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContainerWidget(int bubbleRadius, QWidget *parent = nullptr);
    void bubble1(BubbleView *b){m_bubble1=b;}
    void bubble2(BubbleView *b){m_bubble2=b;}
    void bubble3(BubbleView *b){m_bubble3=b;}

    void deletePrevious();
    void updateView(BubbleView *b1, BubbleView *b2, BubbleView *b3);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_containerBackground;
    BubbleView *m_bubble1 = nullptr;
    BubbleView *m_bubble2 = nullptr;
    BubbleView *m_bubble3 = nullptr;

    QLabel *m_spotBubble1;
    QLabel *m_spotBubble2;
    QLabel *m_spotBubble3;

    QHBoxLayout *m_layout;

};

#endif // CONTAINERWIDGET_H

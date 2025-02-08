#ifndef CONTAINERWIDGET_H
#define CONTAINERWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>

class ContainerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContainerWidget(QWidget *parent = nullptr);
    void spotBubble1(QPixmap p){m_spotBubble1->setPixmap(p);}
    void spotBubble2(QPixmap p){m_spotBubble2->setPixmap(p);}
    void spotBubble3(QPixmap p){m_spotBubble3->setPixmap(p);}

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_containerBackground;
    QLabel *m_spotBubble1;
    QLabel *m_spotBubble2;
    QLabel *m_spotBubble3;
};

#endif // CONTAINERWIDGET_H

#ifndef CANNONWIDGET_H
#define CANNONWIDGET_H

#include <QWidget>

#include "bubbleview.h"

class CannonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CannonWidget(QWidget *parent = nullptr);
    ~CannonWidget();
    void setBubble(BubbleView* b){m_currentBubble = b;}
signals:

protected:
    void paintEvent(QPaintEvent *event) override;


private:
    QPixmap m_cannonImage;
    BubbleView *m_currentBubble;

};

#endif // CANNONWIDGET_H

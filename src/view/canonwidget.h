#ifndef CANONWIDGET_H
#define CANONWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>

#include "src/view/bubbleview.h"

class CanonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanonWidget(int bubbleRadius , int radius = 100, int startX = 125, int startY = 20, QWidget *parent = nullptr);
    ~CanonWidget();

    void keyPressEvent(QKeyEvent *event) override;
    int getStartX() const { return startX; }  // Getter for startX
    int getStartY() const { return startY; }  // Getter for startY

    int startX, startY;
    void updateBubble(BubbleView *b);

signals:
    void shootSignal();
    void updateAngle(int direction);


protected:
    void paintEvent(QPaintEvent *event) override;


public slots:
    void onAngleChanged(qreal newAngle); // Slot to handle angle changes

private:
    int m_currentAngle = 90;
    int m_radius;
    QPen pen;
    BubbleView *m_bubble = nullptr;
    QLabel *m_spotBubble = nullptr;
    QHBoxLayout *m_layout = nullptr;



};


#endif // CANONWIDGET_H

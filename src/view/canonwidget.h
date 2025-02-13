#ifndef CANONWIDGET_H
#define CANONWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QtMath>

class CanonWidget : public QWidget {
    Q_OBJECT

public:
    explicit CanonWidget(QWidget *parent = nullptr, int radius = 50, int startX = 100, int startY = 100);
    ~CanonWidget();

    qreal getAngle() const;
    void keyPressEvent(QKeyEvent *event) override;

protected:
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override;

private:
    void updateAngle(int direction);

private:
    qreal angle;
    int m_radius;
    int startX, startY;
    QPen pen;
};


#endif // CANONWIDGET_H

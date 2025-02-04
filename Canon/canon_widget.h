#ifndef WIDGET_H
#define WIDGET_H

#include "ui_canon_widget.h"

#include <QtQuickWidgets/QQuickWidget>
#include <QPointF>
#include <QPainter>
#include <QVBoxLayout>
#include <QtQml/QQmlContext>
#include <QPixmap>
#include <QMouseEvent>

class CanonWidget : public QWidget, private Ui::Widget
{
    Q_OBJECT

public:
    CanonWidget(QWidget *parent = nullptr);
    ~CanonWidget();

signals:
    void fireBubble(QPointF start, QPointF end); // Signal to fire a bubble

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPointF calculateFireEndPosition(); // Method to calculate where the bubble will go
    QPixmap cannonImage; // image de Canon
    float rotationAngle;

};
#endif // WIDGET_H

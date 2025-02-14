#ifndef CANONWIDGET_H
#define CANONWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QtMath>
#include "src/model/canonmodel.h"

class CanonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanonWidget(QWidget *parent = nullptr,CanonModel *m_model=nullptr , int radius = 100, int startX = 125, int startY = 200);
    ~CanonWidget();

    void setModel(CanonModel *model); // Set the model
    void keyPressEvent(QKeyEvent *event) override;

protected:
    void paintEvent(QPaintEvent *event) override;
     QSize sizeHint() const override;

private slots:
    void onAngleChanged(qreal newAngle); // Slot to handle angle changes

private:
    CanonModel *m_model; // Pointer to the model
    int m_radius;
    int startX, startY;
    QPen pen;
};

#endif // CANONWIDGET_H

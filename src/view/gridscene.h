#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "bubbleview.h"

class GridScene : public QGraphicsView {
    Q_OBJECT
public:
    GridScene(int windowWidth, int windowHeight, int gridRadius, int bubbleRadius, QWidget *parent = nullptr);
    QPointF localCenter()const {return m_localCenter;}
    QPointF globalCenter()const {return m_globalCenter;}
    QPointF globalOrigin() const {return m_globalOrigin;}
    int width() const {return m_width;}
    int height() const {return m_height;}
    int gridRadius() {return m_gridRadius;}
    int bubbleRadius() {return m_bubbleRadius;}

    void width(int w){m_width=w;}
    void height(int h){m_height=h;}

public slots:
    void onBubbleAdded(Bubble *b);
    void onBubbleDestroyed(Bubble *b);
    void onBubbleMoved(int prevRow, int prevCol, Bubble *b);

private:

    QPointF m_localCenter;
    QPointF m_globalCenter;
    QPointF m_globalOrigin;
    int m_width, m_height;
    int m_nrows, m_ncols;
    int m_gridRadius;
    int m_bubbleRadius;
    QVector<QVector<BubbleView*>> m_bubbleMatrix;
};

#endif // GRIDSCENE_H

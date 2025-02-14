#include "gridscene.h"
#include <QColor>
#include <QBrush>
#include <QScreen>
#include <QRect>
#include <QGuiApplication>

GridScene::GridScene(int windowWidth, int windowHeight, int gridRadius, int bubbleRadius,  QWidget *parent)
    : QGraphicsView{parent}, m_gridRadius{gridRadius}, m_bubbleRadius{bubbleRadius}
{
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setBackgroundBrush(QBrush(QColor(173, 216, 230)));

    setScene(scene);

    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::TextAntialiasing);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_width = windowWidth * 0.7;
    m_height = windowHeight * 0.5;
    setFixedSize(m_width,m_height);

    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setSceneRect(0, 0, m_width, m_height);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTransformationAnchor(QGraphicsView::NoAnchor);
    setDragMode(QGraphicsView::NoDrag);


    m_localCenter = QPoint(m_width/2.f,m_height/2.f);
    int widthDiff = windowWidth - m_width;
    int heightDiff = windowHeight - m_height;

    m_globalCenter = QPointF(m_localCenter.x() + widthDiff/2.f, m_localCenter.y() + heightDiff/2.f);
    m_globalOrigin = QPointF(m_globalCenter.x()-m_width/2.f, m_globalCenter.y()-m_height/2.f);

    m_ncols = m_width/(2*m_gridRadius) +1;
    m_nrows = qRound(m_height/(std::sqrt(3)*m_gridRadius));


    m_bubbleMatrix = QVector<QVector<BubbleView*>>(m_nrows, QVector<BubbleView*>(m_ncols, nullptr));
}




void GridScene::onBubbleAdded(Bubble *b) {
    BubbleView* bubbleView = new BubbleView(b->type(),m_bubbleRadius);
    QVector<int> pos = b->gridPosition();
    m_bubbleMatrix[pos[0]][pos[1]] = bubbleView;

    bubbleView->setPos(b->position());
    scene()->addItem(bubbleView);
}

void GridScene::onBubbleDestroyed(Bubble* b) {
    if (!b) return;
    QVector<int> pos = b->gridPosition();
    scene()->removeItem(m_bubbleMatrix[pos[0]][pos[1]]);
    delete m_bubbleMatrix[pos[0]][pos[1]] ;
    m_bubbleMatrix[pos[0]][pos[1]] = nullptr;
}

void GridScene::onBubbleMoved(int prevRow, int prevCol, Bubble* b) {
    if (!b) return;
    BubbleView* bubbleView = m_bubbleMatrix[prevRow][prevCol];
    scene()->removeItem(m_bubbleMatrix[prevRow][prevCol]);

    QVector<int> pos = b->gridPosition();
    m_bubbleMatrix[pos[0]][pos[1]] = bubbleView;
    bubbleView->setPos(b->position());
    scene()->addItem(bubbleView);

    delete m_bubbleMatrix[prevRow][prevCol] ;
    m_bubbleMatrix[prevRow][prevCol] = nullptr;
}


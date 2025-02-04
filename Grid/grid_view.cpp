#include "Grid/grid_view.h"
#include <QKeyEvent>
#include <QDebug>

GridView::GridView(GridLogic *scene, QWidget *parent)
    : QGraphicsView(scene, parent), m_gridLogic(scene) {
    // Connect signals from GridLogic to the corresponding slots in GridView
    connect(m_gridLogic, &GridLogic::bubblePopped, this, &GridView::onBubblePopped);
    connect(m_gridLogic, &GridLogic::rowAdded, this, &GridView::onRowAdded);
    connect(m_gridLogic, &GridLogic::gameOver, this, &GridView::onGameOver);

    // Set basic properties of the view
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::TextAntialiasing);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);

    setAlignment(Qt::AlignCenter);
    int grid_view_width = m_gridLogic->getColCount()* 2*m_gridLogic->getBubbleRadius();
    grid_view_width += (m_gridLogic->getColCount()) * m_gridLogic->getGraphicalOffset();
    grid_view_width += 2*m_gridLogic->getBubbleRadius();
    int grid_view_height = m_gridLogic->getColCount()* 2*m_gridLogic->getBubbleRadius();
    grid_view_height += (m_gridLogic->getColCount()) * m_gridLogic->getGraphicalOffset();
    setMinimumSize(grid_view_width, grid_view_height);

}

void GridView::onBubblePopped(int row, int col) {
    qDebug() << "Bubble popped at (" << row << "," << col << ")";
    // Handle any additional UI updates here when a bubble is popped
}

void GridView::onRowAdded() {
    qDebug() << "New row added!";
    // Handle any UI updates when a row is added, such as adjusting the view
}

void GridView::onGameOver() {
    qDebug() << "Game over bien recu par Grid View!";
    m_gridLogic->popBubbles();

    // Ajouter un texte "Game Over" au centre de la scène
    QGraphicsTextItem *gameOverText = new QGraphicsTextItem("Game Over");
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setFont(QFont("Arial", 32, QFont::Bold));

    // Centrer le texte sur la scène
    QRectF sceneBounds = m_gridLogic->sceneRect();
    gameOverText->setPos(sceneBounds.center().x() - gameOverText->boundingRect().width() / 2,
                         sceneBounds.center().y() - gameOverText->boundingRect().height() / 2);

    // Ajouter le texte à la scène
    m_gridLogic->addItem(gameOverText);
}


void GridView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A) // Check if "A" is pressed
    {
        qDebug() << "Key A pressed! Adding a row...";
        m_gridLogic->addRow(); // Call GridLogic to add a row
    }
    else
    {
        QGraphicsView::keyPressEvent(event); // Pass event to parent if not handled
    }
}

#include "gridscene.h"
#include <QColor>
#include <QBrush>
#include <QScreen>
#include <QRect>
#include <QGuiApplication>

GridScene::GridScene(GridModel *model, int bubble_radius, int graphic_offset, int nb_cols, int nb_rows, int nb_max_rows, QWidget *parent)
    : QGraphicsView{parent},
    m_graphic_offset{graphic_offset},
    m_bubble_radius{bubble_radius},
    m_nb_cols{nb_cols},
    m_nb_rows{nb_rows},
    m_nb_max_rows{nb_max_rows},
    m_grid(nb_max_rows, QVector<BubbleView*>(nb_cols, nullptr))
{
    setupUi();
    connectToModel(model);

    setFocusPolicy(Qt::StrongFocus);  // Ensure it can accept focus
    setFocus();  // Set focus on GridModel
}

void GridScene::setupUi() {

    QGraphicsScene *scene = new QGraphicsScene();
    scene->setBackgroundBrush(QBrush(QColor(173, 216, 230)));

    setScene(scene);

    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::TextAntialiasing);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    int width = screenGeometry.width() * 0.6;
    int height = screenGeometry.height() * 0.5;

    setFixedSize(width, height);

}


void GridScene::connectToModel(GridModel *model) {
    connect(model, &GridModel::bubbleAdded, this, &GridScene::onBubbleAdded);
    connect(model, &GridModel::bubblePopped, this, &GridScene::onBubblePopped);
    connect(model, &GridModel::rowAdded, this, &GridScene::onRowAdded);
    connect(model, &GridModel::gameOver, this, &GridScene::onGameOver);



    connect(this, &GridScene::addRowRequested, model, &GridModel::addNewLineOfBubbles);
    connect(this, &GridScene::addRandomBubbleRequested, model, &GridModel::addRandomBubbleInAvaibleSpace);


}

void GridScene::onBubbleAdded(Bubble* bubble, bool offset) {
    int row = bubble->position().x();
    int col = bubble->position().y();

    BubbleView* bubbleView = new BubbleView( bubble,
                                            m_bubble_radius, offset);
    m_grid[row][col] = bubbleView;
    //bubbleView->setPos(x, y);
    scene()->addItem(bubbleView);
}

void GridScene::onBubblePopped(Bubble* bubble) {
    if (!bubble) return;

    int row = bubble->position().x();
    int col = bubble->position().y();

    bubble->popped();
    scene()->removeItem(m_grid[row][col] );
    delete m_grid[row][col] ;
    m_grid[row][col] = nullptr;
}

void GridScene::onRowAdded() {
    qDebug() << "New row added!";
    redrawAllRows();
}



void GridScene::onGameOver() {
    qDebug() << "Game over received by Grid View!";

    // Clear all bubbles from the scene
    scene()->clear();

    // Add a "Game Over" message
    QGraphicsTextItem *gameOverText = new QGraphicsTextItem("Game Over");
    gameOverText->setDefaultTextColor(Qt::red);
    gameOverText->setFont(QFont("Arial", 32, QFont::Bold));

    // Center the text on the scene
    QRectF sceneBounds = scene()->sceneRect();
    gameOverText->setPos(sceneBounds.center().x() - gameOverText->boundingRect().width() / 2,
                         sceneBounds.center().y() - gameOverText->boundingRect().height() / 2);

    scene()->addItem(gameOverText);
}



void GridScene::redrawAllRows() {
    qDebug() << "Redrawing all rows in Grid Scene...";


    if (m_nb_rows >= m_nb_max_rows) {
        qDebug() << "Cannot add more rows, maximum reached.";
        return;
    }

    for (int col = 0; col < m_nb_cols; col++) {
        if (m_grid[m_nb_max_rows - 1][col]) {
            m_grid[m_nb_max_rows - 1][col] = nullptr;
        }
    }


    for (int row = m_nb_max_rows - 2; row >= 0; row--) {
        for (int col = 0; col < m_nb_cols; col++) {
            if (m_grid[row][col]) {
                m_grid[row+1][col] = m_grid[row][col];
            } else {
                m_grid[row][col] = nullptr;
            }
        }
    }
}

void GridScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A) {
        qDebug() << "Key A pressed! Adding a row...";
        emit addRowRequested(); // Call GridLogic to add a row
    }
    else if (event->key() == Qt::Key_B) {
        qDebug() << "Key B pressed! Adding a random Bubble at first row...";
        emit addRandomBubbleRequested();
    }
    else
    {
        QGraphicsView::keyPressEvent(event); // Pass event to parent class
    }
}

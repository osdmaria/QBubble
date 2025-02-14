#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include "bubble.h"

#include <QKeyEvent>

#include <QGraphicsScene>
#include <QVector>
#include <QColor>
#include <QDebug>
#include <QTimer>
#include <QQueue>
#include <QRandomGenerator>

class GridModel : public QGraphicsScene {
    Q_OBJECT

public:
    GridModel(int rows, int cols, QObject *parent = nullptr);

    int getMaxRowCount() const { return m_max_nb_rows; }
    int getCurrRowCount() const { return m_curr_nb_rows; }
    int getColCount() const { return m_nb_cols; }
    int getBubbleRadius() const { return m_bubble_radius; }
    int getGraphicalOffset() const { return m_graphic_offset; }

    void addBubble(int row, int col, QColor color);
    Bubble* addBubble(int row, int col, QColor color, int random);
    bool isFirstRowFull();
    void addNewLineOfBubbles();
    void fillFirstRow();

    void removeBubble(int row, int col);
    bool isFirstRowEmpty();
    void popAllBubbles();

    bool isGameOver();
    QColor getRandomColor();

    QVector<QPair<int, int>>  getSameColorConnectedBubbles(int bubble_row, int bubble_col);
    QVector<QPair<int, int>>  getAccessibleBlankSpace();
    QVector<QPair<int, int>>  getDroppableBubbles();

    void handlePossibleEmptyFirstRow();
    void handlePossibleDroppableBubbles();
    void handlePossiblePoppableBubbles(int row, int col);

    void addRandomBubbleInAvaibleSpace();
    void addBubbleInCanonDirection(int angle);

    void setOffset(int row, bool offset);
    bool getOffset(int row) const;


signals:
    void bubbleAdded(Bubble* bubble, bool offset);
    void bubblePopped(Bubble* bubble);
    void rowAdded();
    void gameOver();
    void offsetUpdated(int row, bool offset);

public slots:
    void addNewLineOfBubblesRequest(); // Slot for adding a row
    void addRandomBubbleInAvaibleSpaceRequest(); // Slot for adding a random bubble
private:
    int m_max_nb_rows;
    int m_nb_cols;
    int m_curr_nb_rows;
    int m_graphic_offset;
    int m_bubble_radius;
    QVector<QVector<Bubble*>> m_grid;  // 2D array to store bubble references
    QVector<bool> m_offset_tab;  // 2D array to store bubble references
};

#endif // GRIDMODEL_H

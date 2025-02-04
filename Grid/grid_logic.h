#ifndef GRIDLOGIC_H
#define GRIDLOGIC_H

#include "bubble.h"  // Include the new Bubble header

#include <QGraphicsScene>
#include <QVector>
#include <QColor>
#include <QDebug>
#include <QRandomGenerator>

class GridLogic : public QGraphicsScene {
    Q_OBJECT

public:
    GridLogic(int rows, int cols, QObject *parent = nullptr);

    void addBubble(int row, int col, QColor color);
    void removeBubble(int row, int col);
    void popBubbles();
    void addRow();
    void fillFirstRow();
    QColor getRandomColor();

    int getMaxRowCount() const { return m_max_nb_rows; }
    int getCurrRowCount() const { return m_curr_nb_rows; }
    int getColCount() const { return m_nb_cols; }
    int getBubbleRadius() const { return m_bubble_radius; }
    int getGraphicalOffset() const { return m_graphic_offset; }

signals:
    void bubblePopped(int row, int col);
    void rowAdded();
    void gameOver();

private:
    int m_max_nb_rows;
    int m_nb_cols;
    int m_curr_nb_rows;
    int m_graphic_offset;
    int m_bubble_radius;
    bool m_is_on_left;
    QVector<QVector<Bubble*>> m_grid;  // 2D array to store bubble references (use Bubble* now)
};

#endif // GRIDLOGIC_H

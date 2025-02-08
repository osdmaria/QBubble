#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include <QObject>

#include "bubble.h"

class GridModel : public QObject
{
    Q_OBJECT
public:
    explicit GridModel(int rows, int cols, QObject *parent = nullptr);
    void addBubble(int row, int col, Bubble *bubble);
    Bubble* popBubble(int row, int col);
    void addRow();
    bool isFull();
    void setHigherRow();

signals:
    void bubblePopped(int row, int col);
    void bubbleAdded(int row, int col);
    void rowAdded();

private:
    QVector<QVector<Bubble*>> m_grid;
    int m_higherRow;
    int m_deathLimit;
};

#endif // GRIDMODEL_H

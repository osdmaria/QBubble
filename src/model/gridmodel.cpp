#include "gridmodel.h"

GridModel::GridModel(int rows, int cols, QObject *parent)
    : QObject{parent}
{
    m_deathLimit = rows - 1;
    m_grid = QVector<QVector<Bubble*>>(rows, QVector<Bubble*>(cols, nullptr));

}

void GridModel::addBubble(int row, int col, Bubble *bubble){
    m_grid[row][col] = bubble;
    m_higherRow = (row > m_higherRow ? row : m_higherRow);
    emit bubbleAdded(row,col);
}

Bubble* GridModel::popBubble(int row, int col){
    Bubble *b = m_grid[row][col];
    m_grid[row][col] = nullptr;
    emit bubblePopped(row,col);
    return b;
}

void GridModel::addRow(){
    QVector<Bubble*> newRow(m_grid[0].size(), nullptr);
    m_grid.prepend(newRow);
    emit rowAdded();
}

bool GridModel::isFull(){
    return m_higherRow >= m_deathLimit;
}

void GridModel::setHigherRow(){
    int i=m_grid.size()-1, j=0;
    while(i>=0 && m_grid[i][j]==nullptr){
        if(j >= m_grid[i].size()-1){
            j = 0;
            i--;
        } else {
            j--;
        }
    }
    m_higherRow = i;
}


#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsView>
#include "src/model/gridmodel.h"
#include "src/view/bubbleview.h"

class GridScene : public QGraphicsView {
    Q_OBJECT
public:
    GridScene(GridModel* model, int bubble_radius, int graphic_offset, int nb_cols, int nb_rows, int m_nb_max_rows, QWidget *parent = nullptr);
    void connectToModel(GridModel *model);
    void redrawAllRows();

private slots:
    void onBubbleAdded(Bubble* bubble, bool offset);
    void onBubblePopped(Bubble* bubble);
    void onRowAdded();
    void onGameOver();

protected:
    void keyPressEvent(QKeyEvent *event);

signals:
    void addRowRequested(); // Signal for adding a row
    void addRandomBubbleRequested(); // Signal for adding a random bubble


private:
    void setupUi();

    int m_graphic_offset;
    int m_bubble_radius;
    int m_nb_cols;
    int m_nb_rows;
    int m_nb_max_rows;

    QVector<QVector<BubbleView*>> m_grid;
    QVector<bool> m_offset_tab;  // 2D array to store bubble references

};

#endif // GRIDSCENE_H

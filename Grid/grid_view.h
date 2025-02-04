#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QGraphicsView>
#include "Grid/grid_logic.h"

class GridView : public QGraphicsView {
    Q_OBJECT

public:
    GridView(GridLogic *scene, QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onBubblePopped(int row, int col);
    void onRowAdded();
    void onGameOver();

private:
    GridLogic *m_gridLogic;
};

#endif // GRIDVIEW_H

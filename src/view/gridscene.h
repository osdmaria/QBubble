#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsView>

class GridScene : public QGraphicsView {
    Q_OBJECT
public:
    GridScene(QWidget *parent = nullptr);

private:
    void setupUi();
};

#endif // GRIDSCENE_H

#include "gridscene.h"
#include <QColor>
#include <QBrush>
#include <QScreen>
#include <QRect>
#include <QGuiApplication>

GridScene::GridScene(QWidget *parent)
    : QGraphicsView{parent}
{
    setupUi();
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

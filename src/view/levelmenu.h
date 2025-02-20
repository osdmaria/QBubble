#ifndef LEVELMENU_H
#define LEVELMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QPixmap>

class LevelMenu : public QWidget {
    Q_OBJECT

public:
    explicit LevelMenu(QWidget *parent = nullptr);

signals:
    void levelSelected(int level);
private :
    void paintEvent(QPaintEvent *event);
};

#endif // LEVELMENU_H


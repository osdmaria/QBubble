#ifndef LEVELMENU_H
#define LEVELMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class LevelMenu : public QWidget {
    Q_OBJECT

public:
    explicit LevelMenu(QWidget *parent = nullptr);

signals:
    void levelSelected(int level);
};

#endif // LEVELMENU_H


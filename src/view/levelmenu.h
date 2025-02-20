#ifndef LEVELMENU_H
#define LEVELMENU_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

class LevelMenu : public QDialog {
    Q_OBJECT

public:
    explicit LevelMenu(QWidget *parent = nullptr);
    ~LevelMenu();

signals:
    void levelSelected(int level);

private:
    QPushButton *level1Btn;
    QPushButton *level2Btn;
    QPushButton *level3Btn;
};

#endif // LEVELMENU_H



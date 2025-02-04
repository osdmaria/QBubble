#ifndef BUBBLESCONTAINER_H
#define BUBBLESCONTAINER_H

#include "ui_bubblescontainer.h"

class BubblesContainer : public QWidget, private Ui::BubblesContainer
{
    Q_OBJECT

public:
    explicit BubblesContainer(QWidget *parent = nullptr);
};

#endif // BUBBLESCONTAINER_H

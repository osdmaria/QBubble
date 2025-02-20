#include "LevelMenu.h"

LevelMenu::LevelMenu(QWidget *parent) : QWidget(parent) {

    setFixedSize(300, 200);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *level1Btn = new QPushButton("Niveau 1", this);
    QPushButton *level2Btn = new QPushButton("Niveau 2", this);
    QPushButton *level3Btn = new QPushButton("Niveau 3", this);

    // Style the button
    QString buttonStyle = "QPushButton {"
                          "background-color: #31B472;"
                          "color: #EEFF6A;"
                          "border-radius: 15px;"
                          "font-size: 30px;"
                          "border: 2px solid #EEFF6A;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #aade90;"
                          "}"
                          "QPushButton:pressed {"
                          "background-color: #6c9956;"
                          "}";

    level1Btn->setStyleSheet(buttonStyle);
    level2Btn->setStyleSheet(buttonStyle);
    level3Btn->setStyleSheet(buttonStyle);

    layout->addWidget(level1Btn);
    layout->addWidget(level2Btn);
    layout->addWidget(level3Btn);

    connect(level1Btn, &QPushButton::clicked, this, [this]() { emit levelSelected(1); });
    connect(level2Btn, &QPushButton::clicked, this, [this]() { emit levelSelected(2); });
    connect(level3Btn, &QPushButton::clicked, this, [this]() { emit levelSelected(3); });

    setLayout(layout);
}


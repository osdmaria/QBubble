#include "LevelMenu.h"

LevelMenu::LevelMenu(QWidget *parent) : QDialog(parent) {
    setFixedSize(300, 200);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    QVBoxLayout *layout = new QVBoxLayout(this);

    level1Btn = new QPushButton("Niveau 1", this);
    level2Btn = new QPushButton("Niveau 2", this);
    level3Btn = new QPushButton("Niveau 3", this);

    // Style the buttons
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

    connect(level1Btn, &QPushButton::clicked, this, [this]() { emit levelSelected(1); accept(); });
    connect(level2Btn, &QPushButton::clicked, this, [this]() { emit levelSelected(2); accept(); });
    connect(level3Btn, &QPushButton::clicked, this, [this]() { emit levelSelected(3); accept(); });

    setLayout(layout);
}



void LevelMenu::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap background(":/images/wood.jpg");

    if (!background.isNull()) {
        QPixmap scaledBackground = background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(0, 0, scaledBackground);
    } else {
        qDebug() << "Erreur : Impossible de charger l'image de fond.";
    }

    QWidget::paintEvent(event);
}
LevelMenu::~LevelMenu(){
    delete level1Btn;
    delete level2Btn;
    delete level3Btn;
}

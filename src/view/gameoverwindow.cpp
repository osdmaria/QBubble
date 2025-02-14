#include "gameoverwindow.h"

gameOverWindow::gameOverWindow(QWidget *parent)
    : QDialog(parent)
{
    setupUi();
    connectSignals();
    setFont(QApplication::font());
    setWindowFlag(Qt::FramelessWindowHint);
    if (parent) {
        QWidget *parentWidget = qobject_cast<QWidget*>(parent);
        if (parentWidget) {
            int x = parentWidget->x() + (parentWidget->width() - this->width()) / 2;
            int y = parentWidget->y() + (parentWidget->height() - this->height()) / 2;
            move(x, y);
        }
    }
}





gameOverWindow::~gameOverWindow() {}

void gameOverWindow::setupUi() {

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Game Over", this);
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *replayButton = new QPushButton("Rejouer", this);
    QPushButton *menuButton = new QPushButton("Menu Principal", this);

    buttonLayout->addWidget(replayButton);
    buttonLayout->addWidget(menuButton);

    mainLayout->addLayout(buttonLayout);




}

void gameOverWindow::connectSignals() {
    //connect(m_reprendreButton, &QPushButton::clicked, this, &MainMenuWindow::openMainWindow);
}



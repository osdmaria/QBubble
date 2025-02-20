#include "src/view/gameoverwindow.h"

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

    //Style des boutons
    QString buttonStyle = "QPushButton {"
                          "background-color: #31B472;"
                          "color: #EEFF6A;"
                          "border-radius: 15px;"
                          "font-size: 20px;"
                          "border: 2px solid #EEFF6A;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #aade90;"
                          "}"
                          "QPushButton:pressed {"
                          "background-color: #6c9956;"
                          "}";

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Game Over", this);
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *m_rejouerButton = new QPushButton("Rejouer", this);
    QPushButton *m_menuPrincipalButton = new QPushButton("Menu Principal", this);
    m_rejouerButton->setStyleSheet(buttonStyle);
    m_menuPrincipalButton ->setStyleSheet(buttonStyle);

    buttonLayout->addWidget(m_rejouerButton);
    buttonLayout->addWidget(m_menuPrincipalButton);
    mainLayout->addLayout(buttonLayout);




}

void gameOverWindow::connectSignals() {
    //connect(m_reprendreButton, &QPushButton::clicked, this, &MainMenuWindow::openMainWindow);
}

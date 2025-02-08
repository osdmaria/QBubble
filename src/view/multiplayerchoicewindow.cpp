#include "src/view/multiplayerchoicewindow.h"

MultiplayerChoiceWindow::MultiplayerChoiceWindow(QWidget *parent)
    : QMainWindow{parent}
{
    setupUi();
    connectSignals();
    setFont(QApplication::font());
}

MultiplayerChoiceWindow::~MultiplayerChoiceWindow() {}

void MultiplayerChoiceWindow::connectSignals() {
    connect(m_mainMenuButton, &QPushButton::clicked, this, &MultiplayerChoiceWindow::onMainMenuClicked);
    connect(m_alliesButton, &QPushButton::clicked, this, &MultiplayerChoiceWindow::onAlliesClicked);
    connect(m_enemiesButton, &QPushButton::clicked, this, &MultiplayerChoiceWindow::onEnemiesClicked);
}

void MultiplayerChoiceWindow::setupUi() {

    m_mainMenuButton = new QPushButton("Retour", this);
    m_alliesButton = new QPushButton("Alliés", this);
    m_enemiesButton = new QPushButton("Ennemis", this);

    //Taille des bouttons
    int buttonWidth = this->width() *0.7;
    int buttonHeight = this->height() * 0.2;
    m_mainMenuButton->setFixedSize(buttonWidth, buttonHeight);
    m_alliesButton->setFixedSize(buttonWidth, buttonHeight);
    m_enemiesButton->setFixedSize(buttonWidth, buttonHeight);

    //Style des boutons
    QString buttonStyle = "QPushButton {"
                          "background-color: green;"
                          "color: white;"
                          "border-radius: 15px;"
                          "font-size: 30px;"
                          "border: 2px solid black;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #aade90;"
                          "}"
                          "QPushButton:pressed {"
                          "background-color: #6c9956;"
                          "}";

    m_mainMenuButton->setStyleSheet(buttonStyle);
    m_alliesButton->setStyleSheet(buttonStyle);
    m_enemiesButton->setStyleSheet(buttonStyle);

    //Alignement des bouttons dans le layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addStretch();
    layout->addWidget(m_alliesButton);
    layout->addWidget(m_enemiesButton);
    layout->addWidget(m_mainMenuButton);
    layout->addStretch();
    layout->setSpacing(20);
    layout->setAlignment(m_alliesButton, Qt::AlignHCenter);
    layout->setAlignment(m_enemiesButton, Qt::AlignHCenter);
    layout->setAlignment(m_mainMenuButton, Qt::AlignHCenter);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

#include "src/view/mainmenuwindow.h"

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    connectSignals();
    setFont(QApplication::font());
}

MainMenuWindow::~MainMenuWindow() {}

void MainMenuWindow::setupUi() {

    m_soloButton = new QPushButton("Partie solo", this);
    m_multiplayerButton = new QPushButton("Partie multijoueurs", this);
    m_howToPlayButton = new QPushButton("Comment jouer", this);
    m_quitButton = new QPushButton("Quitter", this);


    //Taille des bouttons
    int buttonWidth = this->width() *0.7;
    int buttonHeight = this->height() * 0.2;
    m_soloButton->setFixedSize(buttonWidth, buttonHeight);
    m_multiplayerButton->setFixedSize(buttonWidth, buttonHeight);
    m_howToPlayButton->setFixedSize(buttonWidth, buttonHeight);
    m_quitButton->setFixedSize(buttonWidth, buttonHeight);

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

    m_soloButton->setStyleSheet(buttonStyle);
    m_multiplayerButton->setStyleSheet(buttonStyle);
    m_howToPlayButton->setStyleSheet(buttonStyle);
    m_quitButton->setStyleSheet(buttonStyle);


    //Alignement des bouttons dans le layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addStretch();
    layout->addWidget(m_soloButton);
    layout->addWidget(m_multiplayerButton);
    layout->addWidget(m_howToPlayButton);
    layout->addWidget(m_quitButton);
    layout->addStretch();
    layout->setSpacing(20);
    layout->setAlignment(m_soloButton, Qt::AlignHCenter);
    layout->setAlignment(m_multiplayerButton, Qt::AlignHCenter);
    layout->setAlignment(m_howToPlayButton, Qt::AlignHCenter);
    layout->setAlignment(m_quitButton, Qt::AlignHCenter);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void MainMenuWindow::connectSignals() {
    connect(m_soloButton, &QPushButton::clicked, this, &MainMenuWindow::onSoloClicked);
    connect(m_multiplayerButton, &QPushButton::clicked, this, &MainMenuWindow::onMultiplayerClicked);
    connect(m_howToPlayButton, &QPushButton::clicked, this, &MainMenuWindow::onHowToPlayClicked);
    connect(m_quitButton, &QPushButton::clicked, this, &MainMenuWindow::onQuitClicked);
}



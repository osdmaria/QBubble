#include "howtoplaywindow.h"

HowToPlayWindow::HowToPlayWindow(QWidget *parent)
    : QMainWindow{parent}
{
    setupUi();
    connectSignals();
    setFont(QApplication::font());

}

void HowToPlayWindow::setupUi() {

    m_mainMenuButton = new QPushButton("Retour", this);

    //Taille des bouttons
    int buttonWidth = this->width() *0.7;
    int buttonHeight = this->height() * 0.2;
    m_mainMenuButton->setFixedSize(buttonWidth, buttonHeight);

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

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addStretch();

    //Title
    QLabel *titleHowToPlayLabel = createTitleHowToPlayLabel();
    layout->addWidget(titleHowToPlayLabel);
    titleHowToPlayLabel->setAlignment(Qt::AlignHCenter);
    layout->setAlignment(titleHowToPlayLabel, Qt::AlignHCenter);

    //Rules
    QLabel *gameRulesLabel = createGameRulesLabel();
    layout->addWidget(gameRulesLabel);
    layout->setAlignment(gameRulesLabel, Qt::AlignHCenter);

    //Controls
    QLabel *gameControlsLabel = createGameControlsLabel();
    layout->addWidget(gameControlsLabel);
    layout->setAlignment(gameControlsLabel, Qt::AlignHCenter);

    //Back to menu
    layout->addWidget(m_mainMenuButton);
    layout->setAlignment(m_mainMenuButton, Qt::AlignHCenter);
    layout->addStretch();

    //Scroll
    QWidget *scrollWidget = new QWidget();
    scrollWidget->setLayout(layout);
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollWidget);

    setCentralWidget(scrollArea);

}


HowToPlayWindow::~HowToPlayWindow() {}

void HowToPlayWindow::connectSignals() {
    connect(m_mainMenuButton, &QPushButton::clicked, this, &HowToPlayWindow::onMainMenuClicked);
}

QLabel* HowToPlayWindow::createTitleHowToPlayLabel() {

    QLabel *titleHowToPlayLabel = new QLabel(this);
    titleHowToPlayLabel->setText("\nComment Jouer ?");
    int width = this->width() *0.7;
    int height = this->height() * 0.2;
    titleHowToPlayLabel->setFixedSize(width,height);

    QString titleHowToPlayLabelStyle = "QLabel {"
                                       "background-color: #d4d286;"
                                       "color: white;"
                                       "border-radius: 1px;"
                                       "font-size: 30px;"
                                       "border: 2px solid black;"
                                       "}";
    titleHowToPlayLabel->setStyleSheet(titleHowToPlayLabelStyle);

    return titleHowToPlayLabel;
}



QLabel* HowToPlayWindow::createGameRulesLabel() {

    QLabel *gameRulesLabel = new QLabel(this);
    gameRulesLabel->setText(
        "bla bla bla\n"
        "A définir\n"
        );

    int width = this->width() * 2 ;
    int height = this->height()*0.5;
    gameRulesLabel->setFixedSize(width,height);

    QString gameRulesLabelStyle = "QLabel {"
                                  "background-color: #d4d286;"
                                  "color: white;"
                                  "border-radius: 1px;"
                                  "font-size: 20px;"
                                  "border: 2px solid black;"
                                  "}";
    gameRulesLabel->setStyleSheet(gameRulesLabelStyle);
    return gameRulesLabel;
}



QLabel* HowToPlayWindow::createGameControlsLabel() {

    QLabel *gameControlsLabel = new QLabel(this);
    gameControlsLabel->setText(
        "bla bla bla\n"
        "A définir\n"
        );

    int width = this->width() * 2 ;
    int height = this->height() * 0.5;
    gameControlsLabel->setFixedSize(width,height);

    QString gameControlsLabelStyle = "QLabel {"
                                  "background-color: #d4d286;"
                                  "color: white;"
                                  "border-radius: 1px;"
                                  "font-size: 20px;"
                                  "border: 2px solid black;"
                                  "}";
    gameControlsLabel->setStyleSheet(gameControlsLabelStyle);
    return gameControlsLabel;
}




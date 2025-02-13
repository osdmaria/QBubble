#include "src/view/multiplayerchoicewindow.h"

MultiplayerChoiceWindow::MultiplayerChoiceWindow(QWidget *parent)
    : QMainWindow{parent},m_music(new Music())
{
    setupUi();
    connectSignals();
    setFont(QApplication::font());
}

MultiplayerChoiceWindow::~MultiplayerChoiceWindow() {}

void MultiplayerChoiceWindow::connectSignals() {
    connect(m_mainMenuButton, &QPushButton::clicked, [this](){
        m_music->playSoundEffect("click");
        emit onMainMenuClicked();});
    connect(m_alliesButton, &QPushButton::clicked, [this](){
        m_music->playSoundEffect("click");
        emit onAlliesClicked();});
    connect(m_enemiesButton, &QPushButton::clicked, [this](){
        m_music->playSoundEffect("click");
        emit onEnemiesClicked();});
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

void MultiplayerChoiceWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap background(":/images/empty_background.png");

    // Vérifier si l'image est correctement chargée
    if (!background.isNull()) {
        // Redimensionner l'image avec une transformation fluide
        QPixmap scaledBackground = background.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Dessiner l'image redimensionnée
        painter.drawPixmap(0, 0, scaledBackground);
    } else {
        qDebug() << "Erreur : Impossible de charger l'image de fond.";
    }

    QMainWindow::paintEvent(event);
}

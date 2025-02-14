#include "src/view/mainmenuwindow.h"
#include <QPainter>
#include <QPixmap>

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    connectSignals();
    setFont(QApplication::font());
}

MainMenuWindow::~MainMenuWindow() {}

void MainMenuWindow::setupUi() {
    // Créer les boutons
    m_soloButton = new QPushButton("Partie solo", this);
    m_multiplayerButton = new QPushButton("Partie multijoueurs", this);
    m_howToPlayButton = new QPushButton("Comment jouer", this);
    m_quitButton = new QPushButton("Quitter", this);

    // Définir la taille des boutons
    int buttonWidth = this->width() * 0.7;
    int buttonHeight = this->height() * 0.19;
    m_soloButton->setFixedSize(buttonWidth, buttonHeight);
    m_multiplayerButton->setFixedSize(buttonWidth, buttonHeight);
    m_howToPlayButton->setFixedSize(buttonWidth, buttonHeight);
    m_quitButton->setFixedSize(buttonWidth, buttonHeight);

    // Style des boutons
    QString buttonStyle = "QPushButton {"
                          "background-color: #31B472;"
                          "color: #EEFF6A;"
                          "border-radius: 15px;"
                          "font-size: 30px;"
                          "border: 2px solid #EEFF6A;"
                          "} "
                          "QPushButton:hover {"
                          "background-color: #aade90;"
                          "} "
                          "QPushButton:pressed {"
                          "background-color: #6c9956;"
                          "}";

    m_soloButton->setStyleSheet(buttonStyle);
    m_multiplayerButton->setStyleSheet(buttonStyle);
    m_howToPlayButton->setStyleSheet(buttonStyle);
    m_quitButton->setStyleSheet(buttonStyle);

    // Créer le bouton du son avec image
    m_imageButton = new QPushButton(this);
    QPixmap buttonImage(":/images/Volume.png");

    if (!buttonImage.isNull()) {
        m_imageButton->setFixedSize(60, 60);  // Taille fixe pour le bouton du son
        m_imageButton->setStyleSheet("QPushButton {"
                                     "border: none;"
                                     "background: transparent;"
                                     "background-color: #31B472;"
                                     "border: 2px solid #EEFF6A;"
                                     "border-radius: 10px; "
                                     "padding: 2px;"
                                     "} "
                                     "QPushButton:hover {"
                                     "background-color: #aade90;"
                                     "}");
        m_imageButton->setIcon(QIcon(buttonImage));
        m_imageButton->setIconSize(QSize(40, 40));  // Taille de l'icône
    } else {
        qDebug() << "Erreur : Impossible de charger l'image du bouton.";
    }

    m_isImageOne = true;
    connect(m_imageButton, &QPushButton::clicked, this, &MainMenuWindow::onImageButtonClicked);

    // Layout pour le bouton son (à droite de la fenêtre)
    QHBoxLayout *soundButtonLayout = new QHBoxLayout();
    soundButtonLayout->addStretch();  // Pousser à droite
    soundButtonLayout->addWidget(m_imageButton);  // Ajouter le bouton du son

    // Layout pour le titre (centré)
    QLabel *title = createTitle();
    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->addStretch();  // Pousser le titre vers le centre
    titleLayout->addWidget(title);  // Ajouter le titre
    titleLayout->addStretch();  // Pousser le titre vers le centre

    // Layout pour les boutons (centré avec espacement)
    QVBoxLayout *buttonsLayout = new QVBoxLayout();
    buttonsLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    buttonsLayout->addWidget(m_soloButton);
    buttonsLayout->addWidget(m_multiplayerButton);
    buttonsLayout->addWidget(m_howToPlayButton);
    buttonsLayout->addWidget(m_quitButton);
    buttonsLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed));
    buttonsLayout->setAlignment(Qt::AlignHCenter);
    // Layout principal pour le titre et les boutons
    QVBoxLayout *mainContentLayout = new QVBoxLayout();
    mainContentLayout->addLayout(titleLayout);  // Ajouter le layout du titre
    mainContentLayout->addLayout(buttonsLayout);  // Ajouter les boutons
    mainContentLayout->addStretch();  // Pousser le contenu vers le haut

    // Layout complet pour la fenêtre (englobant tout)
    QVBoxLayout *fullLayout = new QVBoxLayout();
    fullLayout->addLayout(soundButtonLayout);  // Ajouter le bouton son en haut
    fullLayout->addLayout(mainContentLayout);  // Ajouter le contenu principal

    // Centraliser le widget
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(fullLayout);
    setCentralWidget(centralWidget);
}



void MainMenuWindow::connectSignals() {
    connect(m_soloButton, &QPushButton::clicked, this, &MainMenuWindow::onSoloClicked);
    connect(m_multiplayerButton, &QPushButton::clicked, this, &MainMenuWindow::onMultiplayerClicked);
    connect(m_howToPlayButton, &QPushButton::clicked, this, &MainMenuWindow::onHowToPlayClicked);
    connect(m_quitButton, &QPushButton::clicked, this, &MainMenuWindow::onQuitClicked);
}

void MainMenuWindow::paintEvent(QPaintEvent *event) {
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

QLabel* MainMenuWindow::createTitle() {

    QLabel *title = new QLabel(this);
    title->setText(" MKOBAT's\nQBubble++\n");
    int width = this->width() *0.8;
    int height = this->height() * 0.8;
    title->setFixedSize(width,height);

    QString titleStyle = "QLabel {"
                         "color: #EEFF6A;"
                         "font-size: 80px;"
                         "}";
    title->setStyleSheet(titleStyle);

    return title;
}

void MainMenuWindow::onImageButtonClicked() {
    QPixmap newImage;

    if (m_isImageOne) {
        newImage = QPixmap(":/images/Volume_not.png");
    } else {
        newImage = QPixmap(":/images/Volume.png");
    }

    if (newImage.isNull()) {
        qDebug() << "Erreur : Impossible de charger l'image du bouton.";
    } else {
        m_imageButton->setIcon(QIcon(newImage));
        m_imageButton->setIconSize(newImage.size());
    }

    m_isImageOne = !m_isImageOne;
}



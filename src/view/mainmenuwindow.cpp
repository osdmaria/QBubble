#include "src/view/mainmenuwindow.h"
#include <QPainter>
#include <QPixmap>

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent),m_music(new Music())
{
    setupUi();
    connectSignals();
    setFont(QApplication::font());
}

MainMenuWindow::~MainMenuWindow() {
    delete m_music;
}

void MainMenuWindow::setupUi() {

    m_soloButton = new QPushButton("Partie solo", this);
    m_multiplayerButton = new QPushButton("Partie multijoueurs", this);
    m_howToPlayButton = new QPushButton("Comment jouer", this);
    m_quitButton = new QPushButton("Quitter", this);
    m_imageButton = new QPushButton(this);
    m_isImageOne = true;


    //Taille des bouttons
    int buttonWidth = 448;//this->width() *0.7;
    int buttonHeight = 72;//this->height() * 0.15;
    m_soloButton->setFixedSize(buttonWidth, buttonHeight);
    m_multiplayerButton->setFixedSize(buttonWidth, buttonHeight);
    m_howToPlayButton->setFixedSize(buttonWidth, buttonHeight);
    m_quitButton->setFixedSize(buttonWidth, buttonHeight);

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

    m_soloButton->setStyleSheet(buttonStyle);
    m_multiplayerButton->setStyleSheet(buttonStyle);
    m_howToPlayButton->setStyleSheet(buttonStyle);
    m_quitButton->setStyleSheet(buttonStyle);

    //boutton du son
    // Création du bouton image
    QPixmap buttonImage(":/images/Volume.png");
    if (!buttonImage.isNull()) {
        m_imageButton->setFixedSize(buttonImage.size());
        m_imageButton->setStyleSheet("QPushButton {"
                                     "border: none;"
                                     "background: transparent;"
                                     "background-color: #31B472;"
                                     "border: 2px solid #EEFF6A;"
                                     "border-radius: 10px; "
                                     "Padding : 2px;"
                                     "}"
                                     "QPushButton:hover {"
                                     "background-color: #aade90;"
                                     "}"
                                     );
        m_imageButton->setIcon(QIcon(buttonImage));
        m_imageButton->setIconSize(buttonImage.size());
    } else {
        qDebug() << "Erreur : Impossible de charger l'image du bouton.";
    }

    QHBoxLayout *topRightLayout = new QHBoxLayout();
    topRightLayout->addStretch();
    topRightLayout->addWidget(m_imageButton);

    //Alignement des bouttons dans le layout
    QVBoxLayout *layout = new QVBoxLayout();
    QLabel *Title = createTitle();
    layout->addWidget(Title, 0, Qt::AlignHCenter);


    layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    layout->addWidget(m_soloButton);
    layout->addWidget(m_multiplayerButton);
    layout->addWidget(m_howToPlayButton);
    layout->addWidget(m_quitButton);

    layout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->setAlignment(Qt::AlignHCenter);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // layout->addStretch();
    // layout->addWidget(m_soloButton);
    // layout->addWidget(m_multiplayerButton);
    // layout->addWidget(m_howToPlayButton);
    // layout->addWidget(m_quitButton);
    // layout->addStretch();
    // layout->setSpacing(20);
    // layout->setAlignment(m_soloButton, Qt::AlignHCenter);
    // layout->setAlignment(m_multiplayerButton, Qt::AlignHCenter);
    // layout->setAlignment(m_howToPlayButton, Qt::AlignHCenter);
    // layout->setAlignment(m_quitButton, Qt::AlignHCenter);

    // QWidget *centralWidget = new QWidget(this);
    // centralWidget->setLayout(layout);
    // setCentralWidget(centralWidget);
}

void MainMenuWindow::connectSignals() {
    connect(m_soloButton, &QPushButton::clicked, [this]() {
        m_music->playSoundEffect("click");
        emit onSoloClicked();
    });

    connect(m_multiplayerButton, &QPushButton::clicked, [this]() {
        m_music->playSoundEffect("click");
        emit onMultiplayerClicked();
    });

    connect(m_howToPlayButton, &QPushButton::clicked, [this]() {
        m_music->playSoundEffect("click");
        emit onHowToPlayClicked();
    });

    connect(m_quitButton, &QPushButton::clicked, [this]() {
        m_music->playSoundEffect("click");
        emit onQuitClicked();
    });

    connect(m_imageButton, &QPushButton::clicked, [this]() {
        m_music->playSoundEffect("click");
        emit onImageButtonClicked();
    });

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
    title->setText("\nMKOBAM's\nQBubble++\n");
    int width = this->width() *0.7;
    int height = this->height() * 0.7;
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
    m_isImageOne = !m_isImageOne;

    // Toggle between two images based on the current state
    if (m_isImageOne) {
        newImage = QPixmap(":/images/Volume.png");  // Second image
    } else {
        newImage = QPixmap(":/images/Volume_not.png");  // First image
    }
    if (newImage.isNull()) {
        qDebug() << "Erreur : Impossible de charger l'image du bouton.";
    }

    // Check if the image is loaded successfully
    if (newImage.isNull()) {
        qDebug() << "Erreur : Impossible de charger l'image du bouton.";
    } else {
        // Update button icon
        m_imageButton->setIcon(QIcon(newImage));
        m_imageButton->setIconSize(newImage.size());
        m_imageButton->update();
    }
}

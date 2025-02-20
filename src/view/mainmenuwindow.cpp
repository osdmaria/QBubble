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
    m_quitButton = new QPushButton("Quitter", this);
    //m_loadgameButton  = new QPushButton("Charger", this);
    //m_niveauButton  = new QPushButton("Choisir le niveau", this);

    m_imageButton = new QPushButton(this);
    m_howToPlayButton = new QPushButton(this);
    m_isImageOne = true;


    //Taille des bouttons
    int buttonWidth = this->width() *0.7;
    int buttonHeight = this->height() * 0.15;

    m_soloButton->setFixedSize(buttonWidth, buttonHeight);
    m_multiplayerButton->setFixedSize(buttonWidth, buttonHeight);
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
    m_quitButton->setStyleSheet(buttonStyle);


    
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
        m_imageButton->setIconSize(QSize(40, 40));
    } else {
        qDebug() << "Erreur : Impossible de charger l'image du bouton.";
    }
    QPixmap buttonImagePlay(":/images/how_to_play_icon.png");
    if (!buttonImagePlay.isNull()) {
        m_howToPlayButton->setFixedSize(buttonImagePlay.size());
        m_howToPlayButton->setStyleSheet("QPushButton {"
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
        m_howToPlayButton->setIcon(QIcon(buttonImagePlay));
        m_howToPlayButton->setIconSize(QSize(40, 40));
    } else {
        qDebug() << "Erreur : Impossible de charger l'image du bouton.";
    }


    QHBoxLayout *soundButtonLayout = new QHBoxLayout();
    soundButtonLayout->addStretch(); 
    soundButtonLayout->addWidget(m_imageButton);
    soundButtonLayout->addWidget(m_howToPlayButton);

    QLabel *title = createTitle();
    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->addStretch(); 
    titleLayout->addWidget(title);  
    titleLayout->addStretch();  

    QVBoxLayout *buttonsLayout = new QVBoxLayout();
    buttonsLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    buttonsLayout->addWidget(m_soloButton);
    buttonsLayout->addWidget(m_multiplayerButton);

    buttonsLayout->addWidget(m_quitButton);


    buttonsLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed));
    buttonsLayout->setAlignment(Qt::AlignHCenter);

    
    QVBoxLayout *mainContentLayout = new QVBoxLayout();
    mainContentLayout->addLayout(titleLayout);  
    mainContentLayout->addLayout(buttonsLayout);  
    mainContentLayout->addStretch();  

    QVBoxLayout *fullLayout = new QVBoxLayout();
    fullLayout->addLayout(soundButtonLayout);  
    fullLayout->addLayout(mainContentLayout);  

    // Centraliser le widget
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(fullLayout);
    setCentralWidget(centralWidget);

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

    if (!background.isNull()) {
        QPixmap scaledBackground = background.scaled(size(), Qt::KeepAspectRatio , Qt::SmoothTransformation);
        painter.drawPixmap(0, 0, scaledBackground);
    } else {
        qDebug() << "Erreur : Impossible de charger l'image de fond.";
    }

    QMainWindow::paintEvent(event);
}

QLabel* MainMenuWindow::createTitle() {

    QLabel *title = new QLabel(this);
    title->setText("\nMKOBAT's\nQBubble++\n");
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


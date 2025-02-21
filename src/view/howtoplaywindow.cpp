#include "howtoplaywindow.h"

HowToPlayWindow::HowToPlayWindow(QWidget *parent)
    : QMainWindow{parent},m_music(new Music())
{
    setupUi();
    connectSignals();
    setFont(QApplication::font());

}

void HowToPlayWindow::setupUi() {

    m_mainMenuButton = new QPushButton("Retour", this);

    //Taille des bouttons
    int buttonWidth =448;// this->width() *0.7;
    int buttonHeight =72;// this->height() * 0.2;
    m_mainMenuButton->setFixedSize(buttonWidth, buttonHeight);

    // Style the button
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
    // Create the frame with a border
    QLabel *frame = framing();

    // Create instruction texts with images
    QWidget *text1 = frameTextWithImage("1 - Utiliser les flèches G et D pour faire pivoter <br> le canon.", "://images/keyboard_play.png");
    QWidget *text2 = frameTextWithImage("2 - Utiliser la touche Espace pour tirer.", "://images/spacebar.png");
    QWidget *text3 = frameTextWithImage("3 - Éviter que les bulles depassent la ligne rouge", "");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addStretch();

    // Layout for the frame to organize texts
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    frameLayout->setAlignment(Qt::AlignCenter);
    frameLayout->addWidget(text1);
    frameLayout->addWidget(text2);
    frameLayout->addWidget(text3);
    frame->setLayout(frameLayout);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(frame, 1); // The frame takes available space
    mainLayout->addStretch();
    mainLayout->addWidget(m_mainMenuButton);
    mainLayout->setAlignment(m_mainMenuButton, Qt::AlignHCenter | Qt::AlignBottom);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);


}


HowToPlayWindow::~HowToPlayWindow() {}

void HowToPlayWindow::connectSignals() {
    connect(m_mainMenuButton, &QPushButton::clicked, [this](){
        m_music->playSoundEffect("click");
        emit onMainMenuClicked();});
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

void HowToPlayWindow::paintEvent(QPaintEvent *event) {
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

QLabel* HowToPlayWindow::framing() {
    QLabel *Frame = new QLabel(this);
    Frame->setObjectName("frameLabel"); // Set a unique object name
    Frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    Frame->setStyleSheet("#frameLabel {"
                         "border: 5px solid black;" // Apply only to this QLabel
                         "border-radius: 15px;" // Rounded corners
                         "background-color: rgba(0, 0, 0, 150);" // Semi-transparent background
                         "padding: 10px;" // Space between text and border
                         "}");

    return Frame;
}




QWidget* HowToPlayWindow::frameTextWithImage(const QString &text, const QString &imagePath) {
    // Create a container widget for the text and image
    QWidget *container = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(container);

    // Create the text label
    QLabel *textLabel = new QLabel(text, container);
    textLabel->setAlignment(Qt::AlignLeft); // Align text to the left
    QString titleStyle = "QLabel {"
                         "color: #EEFF6A;"
                         "font-size: 30px;"
                         "font-weight: bold;"
                         "background: transparent;"
                         "}";
    textLabel->setStyleSheet(titleStyle);

    // Create the image label
    QLabel *imageLabel = new QLabel(container);
    QPixmap image(imagePath);
    imageLabel->setPixmap(image);
    imageLabel->setScaledContents(true);
    imageLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); // Set fixed size for image

    // Add the text and image to the layout
    layout->addWidget(textLabel);
    layout->addWidget(imageLabel);

    // Adjust the layout spacing
    layout->setSpacing(10); // Optional: Adjust the spacing between the text and the image

    return container;
}


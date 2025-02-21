#include "src/view/sologamewindow.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPropertyAnimation>
#include <QTimer>
#include "src/model/coloredbubble.h"

SoloGameWindow::SoloGameWindow(int widthSize, int heightSize, QWidget *parent)
    : QMainWindow{parent}, m_music(new Music())
{
    setFixedSize(widthSize,heightSize);
    m_scoreWidget = new ScoreWidget();

    int bubbleRadius = 67;
    m_gridScene = new GridScene(width(),height(),34,bubbleRadius,this);
    m_containerWidget = new ContainerWidget(bubbleRadius);
    setupUi();
    connectSignals();

    m_pauseWindow = nullptr;
    m_gameOverWindow = new gameOverWindow;
    m_menuLevels = new LevelMenu;
}

SoloGameWindow::~SoloGameWindow() {
    qDebug()<<"check score";
    delete m_scoreWidget;
    qDebug()<<"check m_scoreWidget";
    delete m_gridScene;
    qDebug()<<"check m_gridScene";
    delete m_canonWidget;
    qDebug()<<"check m_canonWidget";
    delete m_containerWidget;
    qDebug()<<"check m_containerWidget";
    delete m_music;
    qDebug()<<"check m_music";
    delete m_retour;
    qDebug()<<"check m_retour";
    delete m_pause;
    qDebug()<<"check m_pause";
    delete m_pauseWindow;
    qDebug()<<"check m_pauseWindow";
    delete m_gameOverWindow;
    qDebug()<<"check m_gameOverWindow";

}

void SoloGameWindow::setupUi() {

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    m_scoreWidget->setFixedSize(300, 100);
    m_scoreWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    mainLayout->addWidget(m_scoreWidget);
    m_gridScene->setFocusPolicy(Qt::NoFocus);
    mainLayout->addWidget(m_gridScene);



    m_canonWidget = new CanonWidget(m_gridScene->bubbleRadius(), 25, 100, 100,this); // Add cannon
    m_canonWidget->focusWidget();
    m_canonWidget->setParent(this);
    m_canonWidget->move(475,450);//// Center the canon widget horizontally
    m_canonWidget->show(); // Ensure it's visible



    mainLayout->addWidget(m_containerWidget);
    mainLayout->setAlignment(Qt::AlignCenter);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    m_retour = new QPushButton("X", this);
    m_pause  = new QPushButton("Pause", this);

    m_retour->setFixedSize(35, 40);
    m_pause ->setFixedSize(100, 40);

    QString buttonStyle = "QPushButton {"
                          "background-color: #31B472;"
                          "color: #EEFF6A;"
                          "border-radius: 15px;"
                          "font-size: 28px;"
                          "border: 2px solid #EEFF6A;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #aade90;"
                          "}"
                          "QPushButton:pressed {"
                          "background-color: #6c9956;"
                          "}";

    m_retour->setStyleSheet(buttonStyle);
    m_pause ->setStyleSheet(buttonStyle);
    mainLayout->addWidget(m_retour);
    mainLayout->addWidget(m_pause);

    // Position buttons and widgets on main window
    m_containerWidget->setParent(this);
    m_containerWidget->move(26,450);

    m_gridScene->setParent(this);
    m_gridScene->move(180, 10);

    m_scoreWidget->setParent(this);
    m_scoreWidget->move(985, 50);

    m_retour->setParent(this);
    m_retour->move(20,50);

    m_pause->setParent(this);
    m_pause->move(60, 50);
}


void SoloGameWindow::keyPressEvent(QKeyEvent *event) {
    if (m_canonWidget) {
       m_canonWidget->keyPressEvent(event);
    }
}
void SoloGameWindow::connectSignals() {
    connect(m_retour, &QPushButton::clicked, [this]{
        m_music->playSoundEffect("click");
        emit onRetourClicked();});
    connect(m_pause, &QPushButton::clicked, [this]{
        m_music->playSoundEffect("click");
        emit onPauseClicked();});

}

void SoloGameWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPixmap background("://images/empty_background.png");

    if (!background.isNull()) {
        QPixmap scaledBackground = background.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

        painter.drawPixmap(0, 0, scaledBackground);
    } else {
        qDebug() << "Erreur : Impossible de charger l'image de fond.";
    }

    QMainWindow::paintEvent(event);
}



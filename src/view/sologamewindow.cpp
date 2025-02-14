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
    m_canonModel = new CanonModel();
    m_containerWidget = new ContainerWidget();
    m_gridScene = new GridScene(width(),height(),35,70,this);
    m_containerWidget = new ContainerWidget();
    setupUi();
    connectSignals();
    connect(m_canonModel, &CanonModel::shootSignal, this, &SoloGameWindow::shootBubble);
    //connect(m_canonModel, &CanonModel::BubbleShoot, m_gridModel, &GridModel::addBubbleInCanonPosition);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

SoloGameWindow::~SoloGameWindow() {}

void SoloGameWindow::setupUi() {

    //widget

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    m_scoreWidget->setFixedSize(300, 30);
    m_scoreWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Add score widget and grid scene
    mainLayout->addWidget(m_scoreWidget);
    mainLayout->addWidget(m_gridScene);

    // Center CanonWidget
    m_canonWidget = new CanonWidget(this, m_canonModel,25, 100, 100); // Add cannon
    qDebug()<<m_canonWidget;
    m_canonWidget->focusWidget();
    m_canonWidget->setParent(this);
    mainLayout->addWidget(m_canonWidget, 0, Qt::AlignHCenter); // Center the canon widget horizontally
    m_canonWidget->show(); // Ensure it's visible


    // Add container widget
    mainLayout->addWidget(m_containerWidget);
    mainLayout->setAlignment(Qt::AlignCenter);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    //button
    m_retour = new QPushButton("X", this);
    m_pause  = new QPushButton("Pause", this);

    // Button sizes
    m_retour->setFixedSize(35, 50);
    m_pause ->setFixedSize(100, 50);

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

    m_retour->setStyleSheet(buttonStyle);
    m_pause ->setStyleSheet(buttonStyle);
    mainLayout->addWidget(m_retour);
    mainLayout->addWidget(m_pause);

    // Position buttons and widgets on main window
    m_containerWidget->setParent(this);
    m_containerWidget->move(26,250);

    m_scoreWidget->setParent(this);
    m_scoreWidget->move(955, 50);

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

void SoloGameWindow::shootBubble(int angle) {
    // // Create a new bubble with a default color (e.g., red) and position
    // QColor bubbleColor = Qt::red; // Example color
    // QPointF startPosition = QPointF(m_canonWidget->getStartX(), m_canonWidget->getStartY()); // Start at the cannon's position
    // ColoredBubble* bubble = new ColoredBubble("bordeaux");

    // // Create a BubbleView to visually represent the bubble
    // BubbleView* bubbleView = new BubbleView("bordeaux", 20, false); // Radius of 20, no offset
    // m_gridScene->scene()->addItem(bubbleView); // Add the bubble to the scene

    // // Calculate the end position of the bubble based on the angle
    // qreal length = 500; // Length of the animation
    // qreal endX = startPosition.x() + length * qCos(qDegreesToRadians(angle));
    // qreal endY = startPosition.y() - length * qSin(qDegreesToRadians(angle)); // Negative Y for upward direction
    // QPointF endPosition(endX, endY);

    // // Create an animation to move the rbubble
    // QPropertyAnimation* animation = new QPropertyAnimation(bubble, "pos");
    // animation->setDuration(1000); // Animation duration in milliseconds
    // animation->setStartValue(startPosition);
    // animation->setEndValue(endPosition);
    // animation->setEasingCurve(QEasingCurve::Linear);

    // // Connect the animation to remove the bubble after it finishes
    // connect(animation, &QPropertyAnimation::finished, [bubbleView, bubble]() {
    //     // Use a timer to remove the bubble after 3 seconds
    //     QTimer::singleShot(3000, [bubbleView, bubble]() {
    //         delete bubbleView; // Remove the visual representation
    //         delete bubble;    // Delete the bubble object
    //     });
    // });

    // // // Start the animation
    // // animation->start();
}

#include "src/view/enemiesgamewindow.h"
#include <QLabel>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsItem>


#include <QPropertyAnimation>
#include <QTimer>
#include "src/model/coloredbubble.h"


EnemiesGameWindow::EnemiesGameWindow(int widthSize, int heightSize, QWidget *parent)
    : QMainWindow{parent}, m_music(new Music())
{
    setFixedSize(widthSize,heightSize);
    m_scoreWidget = new ScoreWidget();
    m_scoreWidget2 = new ScoreWidget();
    int bubbleRadius = 67;
    m_gridScene = new GridScene(width(),height(), 34,bubbleRadius,this);

    m_containerWidget = new ContainerWidget(bubbleRadius);
    m_containerWidget2 = new ContainerWidget(bubbleRadius);
    setupUi();
    connectSignals();

    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

EnemiesGameWindow::~EnemiesGameWindow(){}

void EnemiesGameWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    m_scoreWidget->setFixedSize(300, 30);
    m_scoreWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_scoreWidget2->setFixedSize(300, 30);
    m_scoreWidget2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    mainLayout->addWidget(m_scoreWidget);
    mainLayout->addWidget(m_scoreWidget2);
    mainLayout->addWidget(m_gridScene);

    // Center CanonWidget
    m_canonWidget = new CanonWidget(m_gridScene->bubbleRadius(), 25, 100, 100,this); // Add cannon
    qDebug()<<m_canonWidget;
    m_canonWidget->focusWidget();
    m_canonWidget->setParent(this);
    m_canonWidget->move(420,500);// Center the canon widget horizontally
    m_canonWidget->show(); // Ensure it's visible

    // Center CanonWidget2
    m_canonWidget2 = new CanonWidget(m_gridScene->bubbleRadius(), 25, 100, 100,this); // Add cannon
    qDebug()<<m_canonWidget2;
    m_canonWidget2->focusWidget();
    m_canonWidget2->setParent(this);
    m_canonWidget2->move(530,500);
    m_canonWidget2->show(); // Ensure it's visible

    // Add container widget
    mainLayout->addWidget(m_containerWidget);
    mainLayout->addWidget(m_containerWidget2);
    mainLayout->setAlignment(Qt::AlignCenter);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    //button
    m_retour = new QPushButton("X", this);
    m_pause  = new QPushButton("Pause", this);

    // Button sizes
    m_retour->setFixedSize(35, 40);
    m_pause ->setFixedSize(100, 40);

    //Style des boutons
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
    m_containerWidget2->setParent(this);
    m_containerWidget2->move(800,450);

    m_gridScene->setParent(this);
    m_gridScene->move(180, 10);

    m_scoreWidget->setParent(this);
    m_scoreWidget->move(970, 50);

    m_scoreWidget2->setParent(this);
    m_scoreWidget2->move(50, 50);

    m_retour->setParent(this);
    m_retour->move(20,10);

    m_pause->setParent(this);
    m_pause->move(60, 10);

}

void EnemiesGameWindow::keyPressEvent(QKeyEvent *event) {
    if (m_canonWidget) {
        m_canonWidget->keyPressEvent(event);
    }
}

void EnemiesGameWindow::connectSignals() {
    connect(m_retour, &QPushButton::clicked, [this]{
        m_music->playSoundEffect("click");
        emit onRetourClicked1();});
    connect(m_pause, &QPushButton::clicked, [this]{
        m_music->playSoundEffect("click");
        emit onPauseClicked1();});

}

void EnemiesGameWindow::paintEvent(QPaintEvent *event) {
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

void EnemiesGameWindow::shootBubble(int angle) {
    //     // Créez une nouvelle bulle avec une couleur et une position de départ
    //     QColor bubbleColor = Qt::red; // Exemple de couleur
    //     QPointF startPosition = QPointF(m_gridScene->width()/2,0); // Position de départ au niveau du canon
    //     Bubble* bubble = new Bubble(bubbleColor, startPosition, this);

    //     // Créez une vue pour la bulle
    //     BubbleView* bubbleView = new BubbleView(bubble, 20, false); // Rayon de 20, pas de décalage
    //     m_gridScene->scene()->addItem(bubbleView); // Ajoutez la bulle à la scène

    //     // Calculez la position finale en fonction de l'angle
    //     qreal length = 200; // Longueur de l'animation
    //     qreal endX = startPosition.x() + length * qCos(qDegreesToRadians(angle));
    //     qreal endY = startPosition.y() - length * qSin(qDegreesToRadians(angle)); // Y négatif pour aller vers le haut
    //     qDebug() << "positions end:" << endX << endY;
    //     QPointF endPosition(endX, endY);

    //     // Convertir les positions en coordonnées globales pour la scène
    //     QPointF startScenePosition = bubbleView->mapToScene(startPosition) - startPosition;
    //     QPointF endScenePosition = bubbleView->mapToScene(endPosition) - startPosition;

    //     // Créez l'animation en utilisant la fonction animationLinearMovement
    //     QGraphicsItemAnimation* animation = bubbleView->animationLinearMovement(
    //         startScenePosition.x(), startScenePosition.y(), // Position de départ en coordonnées globales
    //         endScenePosition.x(), endScenePosition.y(),     // Position finale en coordonnées globales
    //         1000                                              // Durée de l'animation en millisecondes
    //         );

    //     // Connectez l'animation pour supprimer la bulle après l'animation
    //     QTimeLine* timer = animation->timeLine();
    //     connect(timer, &QTimeLine::finished, [bubbleView, bubble]() {
    //         // Utilisez un timer pour supprimer la bulle après 3 secondes
    //         QTimer::singleShot(3000, [bubbleView, bubble]() {
    //             delete bubbleView; // Supprimez la vue de la bulle
    //             delete bubble;     // Supprimez l'objet bulle
    //         });
    //     });

    //     // Débogage : vérifiez que l'animation est bien démarrée
    //     qDebug() << "Démarrage de l'animation de la bulle";
}

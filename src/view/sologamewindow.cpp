#include "src/view/sologamewindow.h"
#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QPropertyAnimation>
#include <QTimer>

SoloGameWindow::SoloGameWindow(QWidget *parent)
    : QMainWindow{parent}, m_music(new Music())
{
    m_scoreWidget = new ScoreWidget();
    m_gridModel = new GridModel(10,15);
    m_canonModel = new CanonModel();
    m_gridScene = new GridScene(m_gridModel, 20, 10,15, 0, 10, this );
    m_containerWidget = new ContainerWidget();
    setupUi();
    connectSignals();
    connect(m_canonModel, &CanonModel::shootSignal, this, &SoloGameWindow::shootBubble);
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
    m_scoreWidget->move(50, 50);

    // Add score widget and grid scene
    mainLayout->addWidget(m_scoreWidget);
    mainLayout->addWidget(m_gridScene);

    // Center CanonWidget
    m_cannonWidget = new CanonWidget(this, m_canonModel,25, 100, 100); // Add cannon
    qDebug()<<m_cannonWidget;
    m_cannonWidget->focusWidget();
    m_cannonWidget->setParent(this);
    mainLayout->addWidget(m_cannonWidget, 0, Qt::AlignHCenter); // Center the canon widget horizontally
    m_cannonWidget->show(); // Ensure it's visible

    // Add container widget
    mainLayout->addWidget(m_containerWidget);
    mainLayout->setAlignment(Qt::AlignCenter);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    //button
    m_retour = new QPushButton("X", this);
    m_pause  = new QPushButton("Pause", this);

    // Button sizes
    m_retour->setFixedSize(this->height() * 0.07, this->height() * 0.08);
    m_pause ->setFixedSize(this->width() *0.15, this->height() * 0.08);

    // Button styles
    QString buttonStyle = "QPushButton {"
                          "background-color: green;"
                          "color: white;"
                          "border-radius: 10px;"
                          "font-size: 25px;"
                          "border: 2px solid black;"
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
    m_containerWidget->move(0,560);

    m_scoreWidget->setParent(this);
    m_scoreWidget->move(450, 50);

    m_retour->setParent(this);
    m_retour->move(50,50);

    m_pause->setParent(this);
    m_pause->move(90, 50);
}


void SoloGameWindow::keyPressEvent(QKeyEvent *event) {
    if (m_cannonWidget) {
        m_cannonWidget->keyPressEvent(event);
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



void SoloGameWindow::shootBubble(int angle) {
    // Créez une nouvelle bulle avec une couleur et une position de départ
    QColor bubbleColor = Qt::red; // Exemple de couleur
    QPointF startPosition = QPointF(m_gridScene->width()/2,0); // Position de départ au niveau du canon
    Bubble* bubble = new Bubble(bubbleColor, startPosition, this);

    // Créez une vue pour la bulle
    BubbleView* bubbleView = new BubbleView(bubble, 20, false); // Rayon de 20, pas de décalage
    m_gridScene->scene()->addItem(bubbleView); // Ajoutez la bulle à la scène

    // Calculez la position finale en fonction de l'angle
    qreal length = 200; // Longueur de l'animation
    qreal endX = startPosition.x() + length * qCos(qDegreesToRadians(angle));
    qreal endY = startPosition.y() - length * qSin(qDegreesToRadians(angle)); // Y négatif pour aller vers le haut
    qDebug() << "positions end:" << endX << endY;
    QPointF endPosition(endX, endY);

    // Convertir les positions en coordonnées globales pour la scène
    QPointF startScenePosition = bubbleView->mapToScene(startPosition) - startPosition;
    QPointF endScenePosition = bubbleView->mapToScene(endPosition) - startPosition;

    // Créez l'animation en utilisant la fonction animationLinearMovement
    QGraphicsItemAnimation* animation = bubbleView->animationLinearMovement(
        startScenePosition.x(), startScenePosition.y(), // Position de départ en coordonnées globales
        endScenePosition.x(), endScenePosition.y(),     // Position finale en coordonnées globales
        1000                                              // Durée de l'animation en millisecondes
        );

    // Connectez l'animation pour supprimer la bulle après l'animation
    QTimeLine* timer = animation->timeLine();
    connect(timer, &QTimeLine::finished, [bubbleView, bubble]() {
        // Utilisez un timer pour supprimer la bulle après 3 secondes
        QTimer::singleShot(3000, [bubbleView, bubble]() {
            delete bubbleView; // Supprimez la vue de la bulle
            delete bubble;     // Supprimez l'objet bulle
        });
    });

    // Débogage : vérifiez que l'animation est bien démarrée
    qDebug() << "Démarrage de l'animation de la bulle";
}



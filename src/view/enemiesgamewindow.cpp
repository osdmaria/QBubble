#include "src/view/enemiesgamewindow.h"
#include <QLabel>
#include <QPixmap>

EnemiesGameWindow::EnemiesGameWindow(QWidget *parent)
    : QMainWindow{parent}
{
    m_scoreWidget = new ScoreWidget();
    m_scoreWidget2 = new ScoreWidget();
    m_gridModel = new GridModel(10,15);
    m_gridScene = new GridScene(m_gridModel, 20, 10,15, 0, 10, this );
    //m_cannonWidget = new CannonWidget();
    //m_cannonWidget2 = new CannonWidget();
    cannonLayout = new QHBoxLayout();
    m_containerWidget = new ContainerWidget();
    setupUi();
}

EnemiesGameWindow::~EnemiesGameWindow(){}

void EnemiesGameWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *topLayout = new QHBoxLayout();

    m_scoreWidget->setFixedSize(300, 30);
    m_scoreWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_scoreWidget2->setFixedSize(300, 30);
    m_scoreWidget2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    //topLayout->addWidget(m_scoreWidget);
    //topLayout->addWidget(m_scoreWidget2);
    topLayout->setContentsMargins(10, 10, 10, 10);
    topLayout->setSpacing(20);

    //cannonLayout->addWidget(m_cannonWidget);
    //cannonLayout->addWidget(m_cannonWidget2);
    cannonLayout->setAlignment(Qt::AlignCenter);
    cannonLayout->setSpacing(50);

    mainLayout->addLayout(topLayout);
    //mainLayout->addWidget(m_gridScene);



    // Add an image to the game window
    QLabel *imageLabel = new QLabel(this);
    QPixmap pixmap(":/images/meme.png");  // Adjust the path to your image
    pixmap = pixmap.scaled(pixmap.width(), pixmap.height() +200, Qt::KeepAspectRatio);  // Scale by 1.5x, keep aspect ratio
    imageLabel->setPixmap(pixmap);
    imageLabel->setAlignment(Qt::AlignCenter);  // Center the image
    mainLayout->addWidget(imageLabel);  // Add the image to the layout


    //mainLayout->addWidget(m_cannonWidget);
    //mainLayout->addWidget(m_cannonWidget2);
    //mainLayout->addWidget(m_containerWidget);
    mainLayout->setAlignment(Qt::AlignCenter);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    //setMinimumSize(600, 600);
}

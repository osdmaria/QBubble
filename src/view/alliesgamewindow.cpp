#include "src/view/alliesgamewindow.h"

AlliesGameWindow::AlliesGameWindow(int widthSize, int heightSize, QWidget *parent)
    : QMainWindow{parent}
{
    setFixedSize(widthSize,heightSize);
    m_scoreWidget = new ScoreWidget();
    //m_gridModel = new GridModel(10,15);
    int bubbleRadius = 67;
    m_gridScene = new GridScene(width(),height(), 30,bubbleRadius,this);
    //m_cannonWidget = new CannonWidget();
    //m_cannonWidget2 = new CannonWidget();
    m_containerWidget = new ContainerWidget(bubbleRadius);
    setupUi();
}

AlliesGameWindow::~AlliesGameWindow(){}

void AlliesGameWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *topLayout = new QHBoxLayout();
    QHBoxLayout *cannonLayout = new QHBoxLayout();

    m_scoreWidget->setFixedSize(300, 30);
    m_scoreWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    //topLayout->addWidget(m_scoreWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);

    //cannonLayout->addWidget(m_cannonWidget);
    //cannonLayout->addWidget(m_cannonWidget2);
    cannonLayout->setAlignment(Qt::AlignCenter);
    cannonLayout->setSpacing(50);

    mainLayout->addLayout(topLayout);
    //mainLayout->addWidget(m_gridScene);
    //mainLayout->addWidget(m_cannonWidget);
    //mainLayout->addWidget(m_cannonWidget2);
    //mainLayout->addWidget(m_containerWidget);

    // Add an image to the game window
    QLabel *imageLabel = new QLabel(this);
    QPixmap pixmap(":/images/meme.png");  // Adjust the path to your image
    pixmap = pixmap.scaled(pixmap.width(), pixmap.height() +200, Qt::KeepAspectRatio);  // Scale by 1.5x, keep aspect ratio
    imageLabel->setPixmap(pixmap);
    imageLabel->setAlignment(Qt::AlignCenter);  // Center the image
    mainLayout->addWidget(imageLabel);  // Add the image to the layout


    mainLayout->setAlignment(Qt::AlignCenter);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    //setMinimumSize(600, 600);
}

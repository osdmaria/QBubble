#include "src/view/alliesgamewindow.h"

AlliesGameWindow::AlliesGameWindow(QWidget *parent)
    : QMainWindow{parent}
{
    m_scoreWidget = new ScoreWidget();
    m_gridModel = new GridModel(10,15);
    m_gridScene = new GridScene(m_gridModel, 20, 10,15, 0, 10, this );
    //m_cannonWidget = new CannonWidget();
    //m_cannonWidget2 = new CannonWidget();
    m_containerWidget = new ContainerWidget();
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

    topLayout->addWidget(m_scoreWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);

    //cannonLayout->addWidget(m_cannonWidget);
    //cannonLayout->addWidget(m_cannonWidget2);
    cannonLayout->setAlignment(Qt::AlignCenter);
    cannonLayout->setSpacing(50);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_gridScene);
    //mainLayout->addWidget(m_cannonWidget);
    //mainLayout->addWidget(m_cannonWidget2);
    mainLayout->addWidget(m_containerWidget);
    mainLayout->setAlignment(Qt::AlignCenter);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    //setMinimumSize(600, 600);
}

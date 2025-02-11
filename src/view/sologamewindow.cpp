#include "src/view/sologamewindow.h"

SoloGameWindow::SoloGameWindow(QWidget *parent)
    : QMainWindow{parent}
{
    m_scoreWidget = new ScoreWidget();
    m_gridModel = new GridModel(10,15);
    m_gridScene = new GridScene(m_gridModel, 20, 10,15, 0, 10, this );
    m_cannonWidget = new CannonWidget();
    m_containerWidget = new ContainerWidget();
    setupUi();
}

SoloGameWindow::~SoloGameWindow() {}

void SoloGameWindow::setupUi() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *topLayout = new QHBoxLayout();

    m_scoreWidget->setFixedSize(300, 30);
    m_scoreWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    topLayout->addWidget(m_scoreWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_gridScene);
    mainLayout->addWidget(m_cannonWidget);
    mainLayout->addWidget(m_containerWidget);
    mainLayout->setAlignment(Qt::AlignCenter);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    //taille mainwwindow
    //setMinimumSize(640, 1270);
    //resize(640, 1270);

    // Thêm khẩu pháo vào cửa sổ chính và đặt vị trí
    m_cannonWidget->setParent(this);  // Quan trọng: Đặt parent là SoloGameWindow
    m_cannonWidget->move(540, 600);   // Đặt vị trí mong muốn
}

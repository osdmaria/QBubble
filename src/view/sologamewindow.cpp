#include "src/view/sologamewindow.h"

SoloGameWindow::SoloGameWindow(QWidget *parent)
    : QMainWindow{parent}
{
    m_scoreWidget = new ScoreWidget();
    m_gridModel = new GridModel(10,15);
    m_gridScene = new GridScene(m_gridModel, 20, 10,15, 0, 10, this );
    m_containerWidget = new ContainerWidget();
    setupUi();
    connectSignals();
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
    m_cannonWidget = new CanonWidget(this, 25, 100, 100); // Add cannon
    m_cannonWidget->focusWidget();
    m_cannonWidget->setParent(this);
    mainLayout->addWidget(m_cannonWidget, 0, Qt::AlignHCenter); // Center the canon widget horizontally

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
    connect(m_retour, &QPushButton::clicked, this, &SoloGameWindow::onRetourClicked);
    connect(m_pause, &QPushButton::clicked, this, &SoloGameWindow::onPauseClicked);

}

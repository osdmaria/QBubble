#include "enemiesgamecontroller.h"

EnemiesGameController::EnemiesGameController(EnemiesGameWindow *enemiesGameView,MainMenuWindow *mainMenuView, QObject *parent)
    : QObject{parent}, m_enemiesGameView{enemiesGameView},m_mainMenuView{mainMenuView}
{
    m_scoreModel = new ScoreModel();
    m_containerModel = new ContainerModel();
    m_canonModel = new CanonModel();
    m_bubbleGeneratorModel = new GeneratorModel();
    m_pauseWindow = nullptr;

    m_hexGridModel = new HexGridModel(enemiesGameView->gridScene()->width(),
                                      enemiesGameView->gridScene()->height(),
                                      m_enemiesGameView->gridScene()->gridRadius(),
                                      enemiesGameView->gridScene()->globalOrigin()
                                      );

    connect(m_scoreModel, &ScoreModel::scoreChanged, this, &EnemiesGameController::updateScore);
    connectSignalsButttons1();
    connectGenerator();
    connectContainer();
    connectCannon();
    connectHexGrid();
    connectGridScene();
}

EnemiesGameController::~EnemiesGameController(){
    delete m_scoreModel;
}


void EnemiesGameController::updateScore(int x)
{
    m_enemiesGameView->scoreWidget()->updateLabel(x);
}

void EnemiesGameController::start(){
    emit generateBubblesRow(m_hexGridModel->ncols());
    emit generateBubblesRow(m_hexGridModel->ncols());
}

void EnemiesGameController::connectSignalsButttons1(){
    qDebug() << "connectSignalsButttons() called!";
    connect(m_enemiesGameView, &EnemiesGameWindow::onRetourClicked1, this, &EnemiesGameController::openMainMenu);
    connect(m_enemiesGameView, &EnemiesGameWindow::onPauseClicked1, this, &EnemiesGameController::showPauseWindow);
}

void EnemiesGameController::openMainMenu() {
    delete m_enemiesGameView;
    m_mainMenuView->show();
    emit menuLauched();
}

void EnemiesGameController::connectGenerator(){
    connect(this, &EnemiesGameController::generateSingleBubble, m_bubbleGeneratorModel, &GeneratorModel::genSingleBubble);
    connect(this, &EnemiesGameController::generateBubblesRow, m_bubbleGeneratorModel, &GeneratorModel::genBubblesRow);
}

void EnemiesGameController::connectContainer(){
    connect(m_bubbleGeneratorModel, &GeneratorModel::bubbleGenerated, m_containerModel, &ContainerModel::updateContainer);
}

void EnemiesGameController::connectCannon(){
    connect(m_containerModel, &ContainerModel::containerUpdated, m_canonModel, &CanonModel::loadBubble);
}

void EnemiesGameController::connectHexGrid(){
    connect(m_bubbleGeneratorModel, &GeneratorModel::bubblesRowGenerated, m_hexGridModel, &HexGridModel::addRow);
}

void EnemiesGameController::connectGridScene(){
    connect(m_hexGridModel, &HexGridModel::bubbleAdded, m_enemiesGameView->gridScene(), &GridScene::onBubbleAdded);
    connect(m_hexGridModel, &HexGridModel::bubbleMoved, m_enemiesGameView->gridScene(), &GridScene::onBubbleMoved);
}

void EnemiesGameController::showPauseWindow() {
    qDebug() << "Pause clicked!";

    if (!m_pauseWindow) {
        m_pauseWindow = new pausewindow(m_enemiesGameView);
    }

    m_pauseWindow->exec();
}

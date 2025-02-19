#include "src/delegate/alliesgamecontroller.h"

AlliesGameController::AlliesGameController(AlliesGameWindow *alliesGameView, MainMenuWindow *mainMenuView, QObject *parent)
    : QObject{parent}, m_alliesGameView{alliesGameView},m_mainMenuView{mainMenuView}
{
    m_scoreModel = new ScoreModel();
    m_containerModel = new ContainerModel();
    m_canonModel = new CanonModel();
    m_bubbleGeneratorModel = new GeneratorModel();
    m_pauseWindow = nullptr;

    m_hexGridModel = new HexGridModel(alliesGameView->gridScene()->width(),
                                      alliesGameView->gridScene()->height(),
                                      m_alliesGameView->gridScene()->gridRadius(),
                                      alliesGameView->gridScene()->globalOrigin()
                                      );

    connect(m_scoreModel, &ScoreModel::scoreChanged, this, &AlliesGameController::updateScore);
    connectSignalsButttons();
    connectGenerator();
    connectContainer();
    connectCannon();
    connectHexGrid();
    connectGridScene();
}

AlliesGameController::~AlliesGameController(){
    delete m_scoreModel;
    delete m_containerModel;
    delete m_canonModel;
    delete m_bubbleGeneratorModel;
    delete m_hexGridModel;
}


void AlliesGameController::updateScore(int x)
{
    m_alliesGameView->scoreWidget()->updateLabel(x);
}


void AlliesGameController::start(){
    emit generateBubblesRow(m_hexGridModel->ncols());
    emit generateBubblesRow(m_hexGridModel->ncols());
}

void AlliesGameController::connectSignalsButttons(){
    qDebug() << "connectSignalsButttons() called!";
    connect(m_alliesGameView, &AlliesGameWindow::onRetourClicked1, this, &AlliesGameController::openMainMenu);
    connect(m_alliesGameView, &AlliesGameWindow::onPauseClicked1, this, &AlliesGameController::showPauseWindow);
}

void AlliesGameController::openMainMenu() {
    delete m_alliesGameView;
    m_mainMenuView->show();
    emit menuLauched();
}

void AlliesGameController::connectGenerator(){
    connect(this, &AlliesGameController::generateSingleBubble, m_bubbleGeneratorModel, &GeneratorModel::genSingleBubble);
    connect(this, &AlliesGameController::generateBubblesRow, m_bubbleGeneratorModel, &GeneratorModel::genBubblesRow);
}

void AlliesGameController::connectContainer(){
    connect(m_bubbleGeneratorModel, &GeneratorModel::bubbleGenerated, m_containerModel, &ContainerModel::updateContainer);
}

void AlliesGameController::connectCannon(){
    connect(m_containerModel, &ContainerModel::containerUpdated, m_canonModel, &CanonModel::loadBubble);
}

void AlliesGameController::connectHexGrid(){
    connect(m_bubbleGeneratorModel, &GeneratorModel::bubblesRowGenerated, m_hexGridModel, &HexGridModel::addRow);
}

void AlliesGameController::connectGridScene(){
    connect(m_hexGridModel, &HexGridModel::bubbleAdded, m_alliesGameView->gridScene(), &GridScene::onBubbleAdded);
    connect(m_hexGridModel, &HexGridModel::bubbleMoved, m_alliesGameView->gridScene(), &GridScene::onBubbleMoved);
}

void AlliesGameController::showPauseWindow() {
    qDebug() << "Pause clicked!";

    if (!m_pauseWindow) {
        m_pauseWindow = new pausewindow(m_alliesGameView);
    }

    m_pauseWindow->exec();
}

#include "sologamecontroller.h"

SoloGameController::SoloGameController(SoloGameWindow *soloGameView,MainMenuWindow *mainMenuView, QObject *parent)
    : QObject{parent}, m_soloGameView{soloGameView}, m_mainMenuView{mainMenuView}
{
    m_scoreModel = new ScoreModel();
    m_containerModel = new ContainerModel();
    //m_burstCalculator = new BurstCalculator();
    m_canonModel = new CanonModel();
    m_bubbleGeneratorModel = new GeneratorModel();
    m_pauseWindow = nullptr;

    m_hexGridModel = new HexGridModel(soloGameView->gridScene()->width(),
                                      soloGameView->gridScene()->height(),
                                      m_soloGameView->gridScene()->gridRadius(),
                                      soloGameView->gridScene()->globalOrigin()
                                      );

    connect(m_scoreModel, &ScoreModel::scoreChanged, this, &SoloGameController::updateScore);
    //connectsignal des buttons
    connectSignalsButttons();
    connectGenerator();
    connectContainer();
    connectCannon();
    connectHexGrid();
    connectGridScene();

}

SoloGameController::~SoloGameController(){
    delete m_scoreModel;
}

void SoloGameController::start(){
    emit generateBubblesRow(m_hexGridModel->ncols());
    emit generateBubblesRow(m_hexGridModel->ncols());
}


void SoloGameController::updateScore(int x)
{
    m_soloGameView->scoreWidget()->updateLabel(x);
}

void SoloGameController::connectSignalsButttons(){
    qDebug() << "retour clicked!";
    connect(m_soloGameView, &SoloGameWindow::onRetourClicked, this, &SoloGameController::openMainMenu);
    connect(m_soloGameView, &SoloGameWindow::onPauseClicked, this, &SoloGameController::showPauseWindow);
}

void SoloGameController::openMainMenu() {

    m_soloGameView->hide();
    m_mainMenuView->show();
    emit menuLauched();
}

void SoloGameController::connectGenerator(){
    connect(this, &SoloGameController::generateSingleBubble, m_bubbleGeneratorModel, &GeneratorModel::genSingleBubble);
    connect(this, &SoloGameController::generateBubblesRow, m_bubbleGeneratorModel, &GeneratorModel::genBubblesRow);
}

void SoloGameController::connectContainer(){
    connect(m_bubbleGeneratorModel, &GeneratorModel::bubbleGenerated, m_containerModel, &ContainerModel::updateContainer);
}

void SoloGameController::connectCannon(){
    connect(m_containerModel, &ContainerModel::containerUpdated, m_canonModel, &CanonModel::loadBubble);
}

void SoloGameController::connectHexGrid(){
    connect(m_bubbleGeneratorModel, &GeneratorModel::bubblesRowGenerated, m_hexGridModel, &HexGridModel::addRow);
}

void SoloGameController::connectGridScene(){
    connect(m_hexGridModel, &HexGridModel::bubbleAdded, m_soloGameView->gridScene(), &GridScene::onBubbleAdded);
    connect(m_hexGridModel, &HexGridModel::bubbleMoved, m_soloGameView->gridScene(), &GridScene::onBubbleMoved);
}

void SoloGameController::showPauseWindow() {
    qDebug() << "Pause clicked!";

    if (!m_pauseWindow) {
        m_pauseWindow = new pausewindow(m_soloGameView);
    }

    m_pauseWindow->exec();
}

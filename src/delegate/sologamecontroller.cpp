#include "sologamecontroller.h"

SoloGameController::SoloGameController(SoloGameWindow *soloGameView,MainMenuWindow *mainMenuView, QObject *parent)
    : QObject{parent}, m_soloGameView{soloGameView}, m_mainMenuView{mainMenuView}
{
    m_scoreModel = new ScoreModel();
    m_containerModel = new ContainerModel();
    m_canonModel = new CanonModel();
    m_bubbleGeneratorModel = new GeneratorModel();
    m_pauseWindow = nullptr;
    m_hexGridModel = new HexGridModel(soloGameView->gridScene()->width(),
                                      soloGameView->gridScene()->height(),
                                      m_soloGameView->gridScene()->gridRadius(),
                                      soloGameView->gridScene()->globalOrigin(),
                                      m_soloGameView->canonWidget()->pos()
                                      );
    m_gridInitializer = new GridInitializer(m_hexGridModel);
    m_burstCalculator = new BurstCalculator(m_hexGridModel);


    //connectsignal des buttons
    connectSignalsButttons();
    connectGenerator();
    connectContainer();
    connectCannon();
    connectHexGrid();
    connectGridScene();
    connectScore();
    connectBurstCalculator();

}

SoloGameController::~SoloGameController(){
    delete m_scoreModel;
}

void SoloGameController::start(){
    m_running = true;
    m_gameOver = false;
    m_gameWon = false;

    loadLevel(2);
    initContainer();
    emit generateSingleBubble();
}


void SoloGameController::initContainer(){
    QVector<Bubble*> vec = {new ColoredBubble("bordeaux"),new ColoredBubble("green"),new ColoredBubble("bordeaux")};
    m_containerModel->initContainer(vec);

}

void SoloGameController::loadLevel(int level){

    switch (level) {
    case 1:
        m_gridInitializer->initLevel1();
        break;
    case 2:
        m_gridInitializer->initLevel2();
        break;
    // case 3:
    //     m_gridInitializer->initLevel3();
    //     break;
    default:
        m_gridInitializer->initLevel1();
        break;
    }
}

void SoloGameController::handleAmountDestroyedBubbles(int amount){
    if(amount==0){
        m_failedShots++;

    } else {
        m_failedShots = 0;
    }

    //qDebug()<<amount<<m_failedShots;

    // if(m_failedShots==3){
    //     emit generateBubblesRow(m_hexGridModel->ncols());
    // }

    if(m_hexGridModel->isGridEmpty())
        gameWon();
    else
        emit generateSingleBubble();
}

void SoloGameController::handleBubblesBurst(Bubble *b){
    ColoredBubble *colored = dynamic_cast<ColoredBubble*>(b);
    ExplosiveBubble *explosive = dynamic_cast<ExplosiveBubble*>(b);

    if(colored){
        emit burstFromColoredBubble(b->gridPosition()[0],b->gridPosition()[1]);
    } else if(explosive) {
        emit burstFromExplosiveBubble(b->gridPosition()[0],b->gridPosition()[1]);
    } else {
    }
    emit generateSingleBubble();
}



void SoloGameController::handleShot(){
    if(m_running && !m_gameOver && !m_gameWon){
        emit shotOrder();
    }
}

void SoloGameController::handleContainer(){
    int bubbleRadius = m_soloGameView->gridScene()->bubbleRadius();
    BubbleView *b1 = new BubbleView(m_containerModel->getBubbleAt(0)->type(),bubbleRadius);
    BubbleView *b2 = new BubbleView(m_containerModel->getBubbleAt(1)->type(),bubbleRadius);
    BubbleView *b3 = new BubbleView(m_containerModel->getBubbleAt(2)->type(),bubbleRadius);
    m_soloGameView->containerWidget()->updateView(b1,b2,b3);
}


void SoloGameController::handleLastRow(){
    gameOver();
}

void SoloGameController::handleLoadCannon(){
    int bubbleRadius = m_soloGameView->gridScene()->bubbleRadius();
    BubbleView *b = new BubbleView(m_canonModel->currentBubble()->type(),bubbleRadius);
    m_soloGameView->canonWidget()->updateBubble(b);

}

void SoloGameController::gameOver(){
    m_gameOver = true;
    m_running = false;
    m_gameWon = false;
    qDebug()<<"GAME OVER";
}

void SoloGameController::gameWon(){
    m_gameOver = true;
    m_running = false;
    m_gameWon = true;
    qDebug()<<"GAME WON";
}

void SoloGameController::openMainMenu() {
    m_soloGameView->hide();
    m_mainMenuView->show();
    emit menuLauched();
}



void SoloGameController::connectSignalsButttons(){
    qDebug() << "connectSignalsButttons() clicked!";
    connect(m_soloGameView, &SoloGameWindow::onRetourClicked, this, &SoloGameController::openMainMenu);
    connect(m_soloGameView, &SoloGameWindow::onPauseClicked, this, &SoloGameController::showPauseWindow);
}

void SoloGameController::connectBurstCalculator(){
    connect(m_burstCalculator,&BurstCalculator::amountDestroyedBubbles,this,&SoloGameController::handleAmountDestroyedBubbles);
    connect(this,&SoloGameController::burstFromColoredBubble,m_burstCalculator,&BurstCalculator::burstFromColoredBubble);
    connect(this,&SoloGameController::burstFromExplosiveBubble,m_burstCalculator,&BurstCalculator::burstFromExplosiveBubble);
}

void SoloGameController::connectScore(){
    connect(m_burstCalculator, &BurstCalculator::bubblesToBurst, m_scoreModel, &ScoreModel::calculScore);
    connect(m_burstCalculator, &BurstCalculator::bubblesDisconnected , m_scoreModel, &ScoreModel::calculScore);
    connect(m_scoreModel, &ScoreModel::calculScoreHandled, m_hexGridModel, &HexGridModel::handleBurst);
    connect(m_scoreModel, &ScoreModel::scoreChanged, m_soloGameView->scoreWidget(),&ScoreWidget::updateLabel);
    //delete m_soloGameView;
    m_mainMenuView->show();
    emit menuLauched();
}

void SoloGameController::connectGenerator(){
    connect(this, &SoloGameController::generateSingleBubble, m_bubbleGeneratorModel, &GeneratorModel::genSingleBubble);
    connect(this, &SoloGameController::generateBubblesRow, m_bubbleGeneratorModel, &GeneratorModel::genBubblesRow);
}

void SoloGameController::connectContainer(){
    connect(m_bubbleGeneratorModel, &GeneratorModel::bubbleGenerated, m_containerModel, &ContainerModel::fill);
    connect(m_containerModel, &ContainerModel::bubblesChanged, this, &SoloGameController::handleContainer);
}

void SoloGameController::connectCannon(){
    connect(m_soloGameView->canonWidget(), &CanonWidget::shootSignal, this, &SoloGameController::handleShot);
    connect(this,&SoloGameController::shotOrder,m_canonModel, &CanonModel::fire);
    connect(m_canonModel, &CanonModel::cannonFired, m_hexGridModel, &HexGridModel::handleShot);
    connect(m_containerModel, &ContainerModel::transmitBubble, m_canonModel, &CanonModel::loadBubble);
    connect(m_soloGameView->canonWidget(), &CanonWidget::updateAngle, m_canonModel, &CanonModel::updateAngle);
    connect(m_canonModel, &CanonModel::angleChanged, m_soloGameView->canonWidget(), &CanonWidget::onAngleChanged);
    connect(m_canonModel, &CanonModel::cannonLoaded, this, &SoloGameController::handleLoadCannon);


}

void SoloGameController::connectHexGrid(){
    connect(m_hexGridModel, &HexGridModel::lastRowReached, this, &SoloGameController::handleLastRow);
    connect(m_hexGridModel, &HexGridModel::shotHandled , this, &SoloGameController::handleBubblesBurst);
    connect(m_hexGridModel, &HexGridModel::findDisconnectedBubbles , m_burstCalculator, &BurstCalculator::burstDisconnectedBubbles);
    connect(m_hexGridModel, &HexGridModel::shotOutOfGrid , m_bubbleGeneratorModel, &GeneratorModel::genSingleBubble);
    connect(m_bubbleGeneratorModel, &GeneratorModel::bubblesRowGenerated, m_hexGridModel, &HexGridModel::addRow);

}

void SoloGameController::connectGridScene(){
    connect(m_hexGridModel, &HexGridModel::bubbleAdded, m_soloGameView->gridScene(), &GridScene::onBubbleAdded);
    connect(m_hexGridModel, &HexGridModel::bubbleDestroyed, m_soloGameView->gridScene(), &GridScene::onBubbleDestroyed);
    connect(m_hexGridModel, &HexGridModel::bubbleMoved, m_soloGameView->gridScene(), &GridScene::onBubbleMoved);
}

void SoloGameController::showPauseWindow() {
    qDebug() << "Pause clicked!";

    if (!m_pauseWindow) {
        m_pauseWindow = new pausewindow(m_soloGameView);
    }

    m_pauseWindow->exec();
}

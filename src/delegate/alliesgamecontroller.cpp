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
                                      alliesGameView->gridScene()->globalOrigin(),
                                      m_alliesGameView->canonWidget()->pos()
                                      );
    m_gridInitializer = new GridInitializer(m_hexGridModel);
    m_burstCalculator = new BurstCalculator(m_hexGridModel);


    connectSignalsButttons();
    connectGenerator();
    connectContainer();
    connectCannon();
    connectHexGrid();
    connectGridScene();
    connectScore();
    connectBurstCalculator();
}

AlliesGameController::~AlliesGameController(){
    delete m_scoreModel;
    delete m_containerModel;
    delete m_canonModel;
    delete m_bubbleGeneratorModel;
    delete m_hexGridModel;
}


void AlliesGameController::start(){
    m_running = true;
    m_gameOver = false;
    m_gameWon = false;

    loadLevel(2);
    initContainer();
    emit generateSingleBubble();
}

void AlliesGameController::initContainer(){
    QVector<Bubble*> vec = {new ColoredBubble("bordeaux"),new ColoredBubble("green"),new ColoredBubble("bordeaux")};
    m_containerModel->initContainer(vec);

}

void AlliesGameController::loadLevel(int level){

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

void AlliesGameController::handleAmountDestroyedBubbles(int amount){
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

void AlliesGameController::handleBubblesBurst(Bubble *b){
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



void AlliesGameController::handleShot(){
    if(m_running && !m_gameOver && !m_gameWon){
        emit shotOrder();
    }
}

void AlliesGameController::handleContainer(){
    int bubbleRadius = m_alliesGameView->gridScene()->bubbleRadius();
    BubbleView *b1 = new BubbleView(m_containerModel->getBubbleAt(0)->type(),bubbleRadius);
    BubbleView *b2 = new BubbleView(m_containerModel->getBubbleAt(1)->type(),bubbleRadius);
    BubbleView *b3 = new BubbleView(m_containerModel->getBubbleAt(2)->type(),bubbleRadius);
    m_alliesGameView->containerWidget()->updateView(b1,b2,b3);
}


void AlliesGameController::handleLastRow(){
    gameOver();
}

void AlliesGameController::handleLoadCannon(){
    int bubbleRadius = m_alliesGameView->gridScene()->bubbleRadius();
    BubbleView *b = new BubbleView(m_canonModel->currentBubble()->type(),bubbleRadius);
    m_alliesGameView->canonWidget()->updateBubble(b);

}

void AlliesGameController::gameOver(){
    m_gameOver = true;
    m_running = false;
    m_gameWon = false;
    qDebug()<<"GAME OVER";
}

void AlliesGameController::gameWon(){
    m_gameOver = true;
    m_running = false;
    m_gameWon = true;
    qDebug()<<"GAME WON";
}

void AlliesGameController::connectSignalsButttons(){
    qDebug() << "connectSignalsButttons() called!";
    connect(m_alliesGameView, &AlliesGameWindow::onRetourClicked1, this, &AlliesGameController::openMainMenu);
    connect(m_alliesGameView, &AlliesGameWindow::onPauseClicked1, this, &AlliesGameController::showPauseWindow);
}

void AlliesGameController::connectBurstCalculator(){
    connect(m_burstCalculator,&BurstCalculator::amountDestroyedBubbles,this,&AlliesGameController::handleAmountDestroyedBubbles);
    connect(this,&AlliesGameController::burstFromColoredBubble,m_burstCalculator,&BurstCalculator::burstFromColoredBubble);
    connect(this,&AlliesGameController::burstFromExplosiveBubble,m_burstCalculator,&BurstCalculator::burstFromExplosiveBubble);
}

void AlliesGameController::connectScore(){
    connect(m_burstCalculator, &BurstCalculator::bubblesToBurst, m_scoreModel, &ScoreModel::calculScore);
    connect(m_burstCalculator, &BurstCalculator::bubblesDisconnected , m_scoreModel, &ScoreModel::calculScore);
    connect(m_scoreModel, &ScoreModel::calculScoreHandled, m_hexGridModel, &HexGridModel::handleBurst);
    connect(m_scoreModel, &ScoreModel::scoreChanged, m_alliesGameView->scoreWidget(),&ScoreWidget::updateLabel);
    //delete m_alliesGameView;
    m_mainMenuView->show();
    emit menuLauched();
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
    connect(m_bubbleGeneratorModel, &GeneratorModel::bubbleGenerated, m_containerModel, &ContainerModel::fill);
    connect(m_containerModel, &ContainerModel::bubblesChanged, this, &AlliesGameController::handleContainer);
}

void AlliesGameController::connectCannon(){
    connect(m_alliesGameView->canonWidget(), &CanonWidget::shootSignal, this, &AlliesGameController::handleShot);
    connect(this,&AlliesGameController::shotOrder,m_canonModel, &CanonModel::fire);
    connect(m_canonModel, &CanonModel::cannonFired, m_hexGridModel, &HexGridModel::handleShot);
    connect(m_containerModel, &ContainerModel::transmitBubble, m_canonModel, &CanonModel::loadBubble);
    connect(m_alliesGameView->canonWidget(), &CanonWidget::updateAngle, m_canonModel, &CanonModel::updateAngle);
    connect(m_canonModel, &CanonModel::angleChanged, m_alliesGameView->canonWidget(), &CanonWidget::onAngleChanged);
    connect(m_canonModel, &CanonModel::cannonLoaded, this, &AlliesGameController::handleLoadCannon);
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

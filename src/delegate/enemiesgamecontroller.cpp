#include "enemiesgamecontroller.h"

EnemiesGameController::EnemiesGameController(EnemiesGameWindow *enemiesGameView, QObject *parent)
    : QObject{parent}, m_enemiesGameView{enemiesGameView}
{
    m_scoreModel = new ScoreModel();
    m_containerModel = new ContainerModel();
    m_canonModel = new CanonModel();
    m_bubbleGeneratorModel = new GeneratorModel();
    m_levelMenu = new LevelMenu();

    m_hexGridModel = new HexGridModel(enemiesGameView->gridScene()->width(),
                                      enemiesGameView->gridScene()->height(),
                                      m_enemiesGameView->gridScene()->gridRadius(),
                                      enemiesGameView->gridScene()->globalOrigin(),
                                      m_enemiesGameView->canonWidget()->pos()
                                      );
    m_gridInitializer = new GridInitializer(m_hexGridModel);
    m_burstCalculator = new BurstCalculator(m_hexGridModel);

    connectGenerator();
    connectContainer();
    connectCannon();
    connectHexGrid();
    connectGridScene();
    connectScore();
    connectBurstCalculator();
}

EnemiesGameController::~EnemiesGameController(){
    delete m_scoreModel;
    delete m_containerModel;
    delete m_bubbleGeneratorModel;
    delete m_burstCalculator;
    delete m_hexGridModel;
    delete m_gridInitializer;
    delete m_canonModel;
    delete m_levelMenu;
}

void EnemiesGameController::start(int level){
    m_running = true;
    m_gameOver = false;
    m_gameWon = false;

    loadLevel(level);
    initContainer();
    emit generateSingleBubble();
}

void EnemiesGameController::initContainer(){
    QVector<Bubble*> vec = {new ColoredBubble("bordeaux"),new ColoredBubble("green"),new ColoredBubble("bordeaux")};
    m_containerModel->initContainer(vec);

}
void EnemiesGameController::startLevelSelection() {
    m_levelMenu->show();
    qDebug() << "startLevelSelection enemies Game...";
    connect(m_levelMenu, &LevelMenu::levelSelected, this, [this](int level) {
        m_levelMenu->close();
        m_levelMenu = nullptr;

        qDebug() << "Level selected:" << level;
        start(level);
    });
}

void EnemiesGameController::loadLevel(int level){

    switch (level) {
    case 1:
        m_gridInitializer->initLevel1();
        break;
    case 2:
        m_gridInitializer->initLevel2();
        break;
    case 3:
        m_gridInitializer->initLevel3();
        break;
    default:
        m_gridInitializer->initLevel1();
        break;
    }
}

void EnemiesGameController::handleAmountDestroyedBubbles(int amount){
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

void EnemiesGameController::handleBubblesBurst(Bubble *b){
    ColoredBubble *colored = dynamic_cast<ColoredBubble*>(b);
    ExplosiveBubble *explosive = dynamic_cast<ExplosiveBubble*>(b);

    if(colored){
        emit burstFromColoredBubble(b->gridPosition()[0],b->gridPosition()[1]);
    } else if(explosive) {
        emit burstFromExplosiveBubble(b->gridPosition()[0],b->gridPosition()[1]);
    } else {
        emit generateSingleBubble();
    }

}



void EnemiesGameController::handleShot(){
    if(m_running && !m_gameOver && !m_gameWon){
        emit shotOrder();
    }
}

void EnemiesGameController::handleContainer(){
    int bubbleRadius = m_enemiesGameView->gridScene()->bubbleRadius();
    BubbleView *b1 = new BubbleView(m_containerModel->getBubbleAt(0)->type(),bubbleRadius);
    BubbleView *b2 = new BubbleView(m_containerModel->getBubbleAt(1)->type(),bubbleRadius);
    BubbleView *b3 = new BubbleView(m_containerModel->getBubbleAt(2)->type(),bubbleRadius);
    m_enemiesGameView->containerWidget()->updateView(b1,b2,b3);
}


void EnemiesGameController::handleLastRow(){
    gameOver();
}

void EnemiesGameController::handleLoadCannon(){
    int bubbleRadius = m_enemiesGameView->gridScene()->bubbleRadius();
    BubbleView *b = new BubbleView(m_canonModel->currentBubble()->type(),bubbleRadius);
    m_enemiesGameView->canonWidget()->updateBubble(b);

}

void EnemiesGameController::gameOver(){
    m_gameOver = true;
    m_running = false;
    m_gameWon = false;
    qDebug()<<"GAME OVER";
}

void EnemiesGameController::gameWon(){
    m_gameOver = true;
    m_running = false;
    m_gameWon = true;
    qDebug()<<"GAME WON";
}


void EnemiesGameController::connectBurstCalculator(){
    connect(m_burstCalculator,&BurstCalculator::amountDestroyedBubbles,this,&EnemiesGameController::handleAmountDestroyedBubbles);
    connect(this,&EnemiesGameController::burstFromColoredBubble,m_burstCalculator,&BurstCalculator::burstFromColoredBubble);
    connect(this,&EnemiesGameController::burstFromExplosiveBubble,m_burstCalculator,&BurstCalculator::burstFromExplosiveBubble);
}

void EnemiesGameController::connectScore(){
    connect(m_burstCalculator, &BurstCalculator::bubblesToBurst, m_scoreModel, &ScoreModel::calculScore);
    connect(m_burstCalculator, &BurstCalculator::bubblesDisconnected , m_scoreModel, &ScoreModel::calculScore);
    connect(m_scoreModel, &ScoreModel::calculScoreHandled, m_hexGridModel, &HexGridModel::handleBurst);
    connect(m_scoreModel, &ScoreModel::scoreChanged, m_enemiesGameView->scoreWidget(),&ScoreWidget::updateLabel);
}


void EnemiesGameController::connectGenerator(){
    connect(this, &EnemiesGameController::generateSingleBubble, m_bubbleGeneratorModel, &GeneratorModel::genSingleBubble);
    connect(this, &EnemiesGameController::generateBubblesRow, m_bubbleGeneratorModel, &GeneratorModel::genBubblesRow);
}

void EnemiesGameController::connectContainer(){
    connect(m_bubbleGeneratorModel, &GeneratorModel::bubbleGenerated, m_containerModel, &ContainerModel::fill);
    connect(m_containerModel, &ContainerModel::bubblesChanged, this, &EnemiesGameController::handleContainer);
}

void EnemiesGameController::connectCannon(){
    connect(m_enemiesGameView->canonWidget(), &CanonWidget::shootSignal, this, &EnemiesGameController::handleShot);
    connect(this,&EnemiesGameController::shotOrder,m_canonModel, &CanonModel::fire);
    connect(m_canonModel, &CanonModel::cannonFired, m_hexGridModel, &HexGridModel::handleShot);
    connect(m_containerModel, &ContainerModel::transmitBubble, m_canonModel, &CanonModel::loadBubble);
    connect(m_enemiesGameView->canonWidget(), &CanonWidget::updateAngle, m_canonModel, &CanonModel::updateAngle);
    connect(m_canonModel, &CanonModel::angleChanged, m_enemiesGameView->canonWidget(), &CanonWidget::onAngleChanged);
    connect(m_canonModel, &CanonModel::cannonLoaded, this, &EnemiesGameController::handleLoadCannon);
}

void EnemiesGameController::connectHexGrid(){
    connect(m_hexGridModel, &HexGridModel::lastRowReached, this, &EnemiesGameController::handleLastRow);
    connect(m_hexGridModel, &HexGridModel::shotHandled , this, &EnemiesGameController::handleBubblesBurst);
    connect(m_hexGridModel, &HexGridModel::findDisconnectedBubbles , m_burstCalculator, &BurstCalculator::burstDisconnectedBubbles);
    connect(m_hexGridModel, &HexGridModel::shotOutOfGrid , m_bubbleGeneratorModel, &GeneratorModel::genSingleBubble);
    connect(m_bubbleGeneratorModel, &GeneratorModel::bubblesRowGenerated, m_hexGridModel, &HexGridModel::addRow);
}

void EnemiesGameController::connectGridScene(){
    connect(m_hexGridModel, &HexGridModel::bubbleAdded, m_enemiesGameView->gridScene(), &GridScene::onBubbleAdded);
    connect(m_hexGridModel, &HexGridModel::bubbleDestroyed, m_enemiesGameView->gridScene(), &GridScene::onBubbleDestroyed);
    connect(m_hexGridModel, &HexGridModel::bubbleMoved, m_enemiesGameView->gridScene(), &GridScene::onBubbleMoved);
}


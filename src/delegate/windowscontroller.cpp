#include "windowscontroller.h"
#include <QFile>

WindowsController::WindowsController(QObject *parent) :QObject(parent)
{
    m_mainMenuView = new MainMenuWindow();
    setFixedSize(m_fixedWidth,m_fixedHeight,m_mainMenuView);
    music = new Music();

    m_howToPlayView = nullptr;
    m_multiplayerChoiceView = nullptr;
    m_alliesGameView = nullptr;
    m_enemiesGameView = nullptr;
    m_soloGameView = nullptr;

    connectSignalsMainMenu();
}


//LAUNCH
void WindowsController::openMainMenu(){
    m_mainMenuView->show();
    if(m_howToPlayView){
        m_howToPlayView->hide();
        delete m_howToPlayView;
        m_howToPlayView = nullptr;
    }

    if(m_multiplayerChoiceView){
        m_multiplayerChoiceView->hide();
        delete m_multiplayerChoiceView;
        m_multiplayerChoiceView = nullptr;
    }

    if(m_alliesGameView){
        m_alliesGameView->hide();
        delete m_alliesGameView;
        m_alliesGameView = nullptr;
    }

    if(m_enemiesGameView){
        m_enemiesGameView->hide();
        delete m_enemiesGameView;
        m_enemiesGameView = nullptr;
    }

    if(m_soloGameView){
        m_soloGameView->hide();
        delete m_soloGameView;
        m_soloGameView = nullptr;
    }
}

void WindowsController::connectSignalsMainMenu(){
    connect(m_mainMenuView, &MainMenuWindow::onSoloClicked, this, &WindowsController::openSoloGame);
    connect(m_mainMenuView, &MainMenuWindow::onMultiplayerClicked, this, &WindowsController::openMultiplayerChoice);
    connect(m_mainMenuView, &MainMenuWindow::onHowToPlayClicked, this, &WindowsController::openHowToPlay);
    connect(m_mainMenuView, &MainMenuWindow::onQuitClicked, this, &WindowsController::quit);
}


//HOW TO PLAY -> open how to play menu
void WindowsController::openHowToPlay() {
    m_howToPlayView = new HowToPlayWindow();
    setFixedSize(m_fixedWidth,m_fixedHeight,m_howToPlayView);
    connectSignalsHowToplay();
    m_howToPlayView->show();
    m_mainMenuView->hide();
    connectSignalsHowToplay();
}

//HOW TO PLAY -> Connect signals
void WindowsController::connectSignalsHowToplay(){
    connect(m_howToPlayView, &HowToPlayWindow::onMainMenuClicked, this, &WindowsController::openMainMenu);
}

//MULTIPLAYER CHOICE -> open multiplayer choice
void WindowsController::openMultiplayerChoice() {
    m_multiplayerChoiceView = new MultiplayerChoiceWindow();
    setFixedSize(m_fixedWidth,m_fixedHeight,m_multiplayerChoiceView);
    m_multiplayerChoiceView->show();
    m_mainMenuView->hide();
    connectSignalsMultiplayerChoice();
}


//MULTIPLAYER CHOICE -> connect signals
void WindowsController::connectSignalsMultiplayerChoice(){
    connect(m_multiplayerChoiceView, &MultiplayerChoiceWindow::onMainMenuClicked, this, &WindowsController::openMainMenu);
    connect(m_multiplayerChoiceView, &MultiplayerChoiceWindow::onAlliesClicked, this, &WindowsController::openAlliesGameWindow);
    connect(m_multiplayerChoiceView, &MultiplayerChoiceWindow::onEnemiesClicked, this, &WindowsController::openEnemiesGameWindow);
}



//SOLO GAME -> openSolo
void WindowsController::openSoloGame() {
    m_soloGameView = new SoloGameWindow(m_fixedWidth,m_fixedHeight);
    m_soloGameView->show();
    if(m_mainMenuView)
        m_mainMenuView->hide();
    emit soloLaunched();
    connectSignalsSolo();
}

void WindowsController::handleGameOver(int score){
    if(m_soloGameView){
        connect(m_soloGameView->gameOver(), &gameOverWindow::replayClicked, this, &WindowsController::replay);
        connect(m_soloGameView->gameOver(), &gameOverWindow::backMenuClicked, this, &WindowsController::handleRetour);
        m_soloGameView->gameOver()->setScore(score);
        m_soloGameView->gameOver()->exec();
    }
    if(m_enemiesGameView){
        connect(m_enemiesGameView->gameOver(), &gameOverWindow::replayClicked, this, &WindowsController::replay);
        connect(m_enemiesGameView->gameOver(), &gameOverWindow::backMenuClicked, this, &WindowsController::handleRetour);
        m_enemiesGameView->gameOver()->setScore(score);
        m_enemiesGameView->gameOver()->exec();
    }
    if(m_alliesGameView){
        connect(m_alliesGameView->gameOver(), &gameOverWindow::replayClicked, this, &WindowsController::replay);
        connect(m_alliesGameView->gameOver(), &gameOverWindow::backMenuClicked, this, &WindowsController::handleRetour);
        m_alliesGameView->gameOver()->setScore(score);
        m_alliesGameView->gameOver()->exec();
    }
}

void WindowsController::replay(){
    if(m_soloGameView){
        if(m_soloGameView->gameOver()){
            m_soloGameView->gameOver()->close();
            m_soloGameView->hide();
            emit soloEnded();
            delete m_soloGameView ;
            openSoloGame();
        }
    }
    if(m_alliesGameView){
        if(m_alliesGameView->gameOver()){
            m_alliesGameView->gameOver()->close();
            m_alliesGameView->hide();
            emit alliesEnded();
            delete m_alliesGameView ;
            openAlliesGameWindow();
        }
    }
    if(m_enemiesGameView){
        if(m_enemiesGameView->gameOver()){
            m_enemiesGameView->gameOver()->close();
            m_enemiesGameView->hide();
            emit enemiesEnded();
            delete m_enemiesGameView ;
            openEnemiesGameWindow();
        }
    }
}

void WindowsController::backMenu(){
    if(m_soloGameView){
        if(m_soloGameView->gameOver()){
            m_soloGameView->gameOver()->close();
            m_soloGameView->hide();
            emit soloEnded();
            delete m_soloGameView ;
        }
    }
    handleRetour();

}



void WindowsController::openAlliesGameWindow() {
    m_alliesGameView = new AlliesGameWindow(m_fixedWidth,m_fixedHeight);
    m_alliesGameView->show();
    if (m_multiplayerChoiceView){
        m_multiplayerChoiceView->hide();
        delete m_multiplayerChoiceView;
        m_multiplayerChoiceView = nullptr;
    }
    emit alliesLauched();
    connectSignalsAllies();
}

void WindowsController::openEnemiesGameWindow() {
    m_enemiesGameView = new EnemiesGameWindow(m_fixedWidth,m_fixedHeight);
    m_enemiesGameView->show();
    if (m_multiplayerChoiceView){
        m_multiplayerChoiceView->hide();
        delete m_multiplayerChoiceView;
        m_multiplayerChoiceView = nullptr;
    }
    emit enemiesLauched();
    connectSignalsEnemies();
}

void WindowsController::startMusic() {
    music->playBackgroundMusic( 0.5);
}


void WindowsController::quit() {
    QApplication::quit();
}


void WindowsController::setFixedSize(int width, int height, QMainWindow *window){
    window->setFixedSize(width,height);
}

void WindowsController::connectSignalsSolo() {
    connect(m_soloGameView, &SoloGameWindow::onRetourClicked, this, &WindowsController::handleRetour);
    connect(m_soloGameView, &SoloGameWindow::onPauseClicked, this, &WindowsController::openPause);
}


void WindowsController::connectSignalsEnemies(){
    connect(m_enemiesGameView, &EnemiesGameWindow::onRetourClicked1, this, &WindowsController::handleRetour);
    connect(m_enemiesGameView, &EnemiesGameWindow::onPauseClicked1, this, &WindowsController::openPause);
}

void WindowsController::connectSignalsAllies(){
    connect(m_alliesGameView, &AlliesGameWindow::onRetourClicked1, this, &WindowsController::handleRetour);
    connect(m_alliesGameView, &AlliesGameWindow::onPauseClicked1, this, &WindowsController::openPause);
}




void WindowsController::handleRetour(){
    if(m_soloGameView)
        emit soloEnded();
    if(m_alliesGameView)
        emit alliesEnded();
    if(m_enemiesGameView)
        emit enemiesEnded();
    openMainMenu();
}

void WindowsController::openPause(){
    if(m_soloGameView){
        if(!m_soloGameView->pauseWindow()){
            m_soloGameView->pauseWindow(new PauseWindow(m_soloGameView));
            connect(m_soloGameView->pauseWindow(), &PauseWindow::reprendreClicked, this, &WindowsController::closePause);
            connect(m_soloGameView->pauseWindow(), &PauseWindow::retryClicked, this, &WindowsController::retry);
            m_soloGameView->pauseWindow()->exec();
        }
    }

    if(m_alliesGameView){
        if(!m_alliesGameView->pauseWindow()){
            m_alliesGameView->pauseWindow(new PauseWindow(m_alliesGameView));
            connect(m_alliesGameView->pauseWindow(), &PauseWindow::reprendreClicked, this, &WindowsController::closePause);
            connect(m_alliesGameView->pauseWindow(), &PauseWindow::retryClicked, this, &WindowsController::retry);
            m_alliesGameView->pauseWindow()->exec();
        }
    }
    if(m_enemiesGameView){
        if(!m_enemiesGameView->pauseWindow()){
            m_enemiesGameView->pauseWindow(new PauseWindow(m_enemiesGameView));
            connect(m_enemiesGameView->pauseWindow(), &PauseWindow::reprendreClicked, this, &WindowsController::closePause);
            connect(m_enemiesGameView->pauseWindow(), &PauseWindow::retryClicked, this, &WindowsController::retry);
            m_enemiesGameView->pauseWindow()->exec();
        }
    }
}

void WindowsController::closePause(){
    if(m_soloGameView){
        if(m_soloGameView->pauseWindow()){
            m_soloGameView->pauseWindow()->close();
            delete m_soloGameView->pauseWindow();
            m_soloGameView->pauseWindow(nullptr);
        }
    }

    if(m_alliesGameView){
        if(m_alliesGameView->pauseWindow()){
            m_alliesGameView->pauseWindow()->close();
            delete m_alliesGameView->pauseWindow();
            m_alliesGameView->pauseWindow(nullptr);
        }
    }
    if(m_enemiesGameView){
        if(m_enemiesGameView->pauseWindow()){
            m_enemiesGameView->pauseWindow()->close();
            delete m_enemiesGameView->pauseWindow();
            m_enemiesGameView->pauseWindow(nullptr);
        }
    }
}

void WindowsController::retry(){
    if(m_soloGameView){
        if(m_soloGameView->pauseWindow()){
            m_soloGameView->pauseWindow()->close();
            m_soloGameView->hide();
            emit soloEnded();
            delete m_soloGameView ;
            openSoloGame();
        }
    }
    if(m_alliesGameView){
        if(m_alliesGameView->pauseWindow()){
            m_alliesGameView->pauseWindow()->close();
            m_alliesGameView->hide();
            emit alliesEnded();
            delete m_alliesGameView ;

            openAlliesGameWindow();
        }
    }
    if(m_enemiesGameView){
        if(m_enemiesGameView->pauseWindow()){
            m_enemiesGameView->pauseWindow()->close();
            m_enemiesGameView->hide();
            emit enemiesEnded();
            delete m_enemiesGameView ;

            openEnemiesGameWindow();
        }
    }
}

void WindowsController::handleReplayTheGame() {
    if (m_soloGameView) {
        m_soloGameView->hide();
        delete m_soloGameView;
        m_soloGameView = nullptr;
    }
    openSoloGame();  // Ouvrir une nouvelle partie solo
}

void WindowsController::handleReturnToMainMenu() {
    openMainMenu();  // Retourner au menu principal
}


void WindowsController::showLevelMenu() {
    LevelMenu *levelMenu = m_soloGameView->menuLevels();

    // Connect the signal before exec() is called
    connect(levelMenu, &LevelMenu::levelSelected, this, [this, levelMenu](int level) {
        emit sendSelectedLevel(level);
        levelMenu->close();  // Close the dialog
        levelMenu->deleteLater();  // Safe deletion after event processing
    });

    levelMenu->exec();  // Modal execution
}


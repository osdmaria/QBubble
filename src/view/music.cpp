#include "Music.h"
#include <QUrl>
#include <QDebug>
#include <QTemporaryFile>
#include <QFile>
#include <QStandardPaths>
Music::Music() {
    musicPlayer = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    musicPlayer->setAudioOutput(audioOutput);
}

void Music::playBackgroundMusic( float volume) {

    QString tempDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    QString finalPath = tempDir + "/BubbleMusicBG.mp3";

    musicPlayer->setSource(QUrl::fromLocalFile(finalPath));

    // if (musicPlayer->error() != QMediaPlayer::NoError) {
    //     qDebug() << "Error:" << musicPlayer->errorString();
    // }

    audioOutput->setVolume(volume);
    QObject::connect(musicPlayer, &QMediaPlayer::mediaStatusChanged, [this](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            musicPlayer->setPosition(0);  // Reset về đầu file
            musicPlayer->play();          // Phát lại nhạc từ đầu
        }
    });
    musicPlayer->play();
}

void Music::stopBackgroundMusic() {
    musicPlayer->stop();
}

void Music::setMusicVolume(float volume) {
    audioOutput->setVolume(volume);
}

void Music::playSoundEffect(const QString &effectName) {
    if (!soundEffects.contains(effectName)) {

        QString tempDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
        QString tempFilePath = tempDir + "/temp_pick.mp3";

        QFile resourceFile(":/Music/pickbutton.mp3");
        if (resourceFile.open(QIODevice::ReadOnly)) {
            QFile tempFile(tempFilePath);
            if (tempFile.open(QIODevice::WriteOnly)) {
                tempFile.write(resourceFile.readAll());
                tempFile.close();
            }
            resourceFile.close();
        } else {
            qDebug() << "can't open qrc.";
            return;
        }

        QMediaPlayer *player = new QMediaPlayer;
        QAudioOutput *audioOutput = new QAudioOutput;
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl::fromLocalFile(tempFilePath));
        audioOutput->setVolume(1);

        soundEffects.insert(effectName, player);
    }

    soundEffects[effectName]->play();
}

void Music::soundEffectExplore(const QString &effectName) {
    if (!soundEffects.contains(effectName)) {

        QString tempDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
        QString tempFilePath = tempDir + "/bubble_explosion.mp3";

        QFile resourceFile(":/Music/bubbleExplosion.mp3");
        if (resourceFile.open(QIODevice::ReadOnly)) {
            QFile tempFile(tempFilePath);
            if (tempFile.open(QIODevice::WriteOnly)) {
                tempFile.write(resourceFile.readAll());
                tempFile.close();
            }
            resourceFile.close();
        } else {
            qDebug() << "can't open qrc.";
            return;
        }

        QMediaPlayer *player = new QMediaPlayer;
        QAudioOutput *audioOutput = new QAudioOutput;
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl::fromLocalFile(tempFilePath));
        audioOutput->setVolume(1);

        soundEffects.insert(effectName, player);
    }

    soundEffects[effectName]->play();
}

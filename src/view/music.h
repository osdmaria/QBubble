#ifndef MUSIC_H
#define MUSIC_H


#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSoundEffect>
#include <QMap>

class Music {
public:
    Music();  // Constructor

    void playBackgroundMusic(float volume = 0.5);
    void stopBackgroundMusic();
    void setMusicVolume(float volume);

    void playSoundEffect(const QString &effectName);
    void soundEffectExplore(const QString &effectName);

private:
    QMediaPlayer *musicPlayer;
    QAudioOutput *audioOutput;
    QMap<QString, QMediaPlayer*> soundEffects;
};

#endif // MUSIC_H

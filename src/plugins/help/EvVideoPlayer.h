#ifndef EVVIDEOPLAYER_H
#define EVVIDEOPLAYER_H

#include "EvWidget.h"

class QSlider;
class QMediaPlayer;
class EvButton;

class EvVideoPlayer : public EvWidget
{
    Q_OBJECT
public:
    explicit EvVideoPlayer(QWidget *parent = 0);

    void setMediaFile(const QString & );

public Q_SLOTS:
    void play();
    void stop();
protected Q_SLOTS:
    void onPlayButtonClicked(bool);
    void onDurationChanged(qint64);
    void onPositionChanged(qint64);
    void onSliderMoved(int);
    void onPlayerStateChanged();
private:
    QMediaPlayer * m_mediaPlayer;
    QSlider * m_positionSlider;
    EvButton * m_playButton;

};

#endif // EVVIDEOPLAYER_H

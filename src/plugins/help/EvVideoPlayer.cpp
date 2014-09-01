#include "EvVideoPlayer.h"
#include <QMediaPlayer>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVideoWidget>
#include "EvButton.h"
#include "EvAppSettings.h"

EvVideoPlayer::EvVideoPlayer(QWidget *parent) :
    EvWidget(parent)
{

    m_mediaPlayer = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
    m_positionSlider = new QSlider(Qt::Horizontal,this);
    m_positionSlider->setRange(0,0);

    m_playButton = new EvButton(this);
    m_playButton->setCheckable(true);

    QVideoWidget *videoWidget = new QVideoWidget(this);
    m_mediaPlayer->setVideoOutput(videoWidget);

    QVBoxLayout * mainLayout =new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    QHBoxLayout * controlsLayout = new QHBoxLayout();
    controlsLayout->setContentsMargins(0,0,0,0);
    controlsLayout->setSpacing(0);


    controlsLayout->addWidget(m_playButton);
    controlsLayout->addWidget(m_positionSlider);
    mainLayout->addWidget(videoWidget);
    mainLayout->addLayout(controlsLayout);


    m_playButton->setIcon(evIconsFactory->applicationIcon(
                              EvIconsFactory::MiniPlay,
                              EvIconsFactory::Light)
                          );
    m_playButton->setPaintMode(EvButton::IconOnly);

    connect(m_playButton,SIGNAL(clicked(bool)),this,SLOT(onPlayButtonClicked(bool)));


    connect(m_mediaPlayer,SIGNAL(stateChanged(QMediaPlayer::State)),
            this,SLOT(onPlayerStateChanged()));

    connect(m_mediaPlayer,SIGNAL(durationChanged(qint64)),
            this,SLOT(onDurationChanged(qint64)));

    connect(m_mediaPlayer,SIGNAL(positionChanged(qint64)),
            this,SLOT(onPositionChanged(qint64)));

    connect(m_positionSlider,SIGNAL(sliderMoved(int)),
            this,SLOT(onSliderMoved(int)));

}

void EvVideoPlayer::setMediaFile(const QString & file)
{
    m_mediaPlayer->setMedia(QUrl::fromLocalFile(file));
}



void EvVideoPlayer::play()
{
    m_mediaPlayer->play();

}

void EvVideoPlayer::stop()
{
    m_mediaPlayer->stop();
}

void EvVideoPlayer::onPlayButtonClicked(bool play)
{
    if(play){
        this->play();
    }
    else {
        stop();
    }
}

void EvVideoPlayer::onDurationChanged(qint64 duration)
{
    m_positionSlider->setRange(0,duration);
}

void EvVideoPlayer::onPositionChanged(qint64 position)
{
    m_positionSlider->setValue(position);
}

void EvVideoPlayer::onSliderMoved(int position)
{
    m_mediaPlayer->setPosition(position);
}

void EvVideoPlayer::onPlayerStateChanged()
{
    switch (m_mediaPlayer->state()) {
    case QMediaPlayer::PlayingState:
        m_playButton->setIcon(evIconsFactory->applicationIcon(
                                  EvIconsFactory::Stop,
                                  EvIconsFactory::Light)
                              );
        break;
    case QMediaPlayer::PausedState:
    case QMediaPlayer::StoppedState:
        m_playButton->setIcon(evIconsFactory->applicationIcon(
                                  EvIconsFactory::MiniPlay,
                                  EvIconsFactory::Light)
                              );

        break;
    default:
        break;
    }
}

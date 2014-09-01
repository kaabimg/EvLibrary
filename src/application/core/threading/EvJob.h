#ifndef EVJOB_H
#define EVJOB_H

#include <QThread>

class EvJob : public QThread
{
    Q_OBJECT
    Q_ENUMS(EvJob::State)

public:
   enum Mode {
           NormalMode = 0x0,
           Blocking = 0x01,
           Pausable = 0x02,
           Stoppable= 0x04,
           Queued = 0x08
       };

    enum State{
        Ready,
        Submitted,
        Started,
        Stopped,
        Paused,
        Finished
    };

    explicit EvJob(QObject *parent = 0);

    Mode mode()const;

    virtual void pause(){}
    virtual void resume(){}
    virtual void stop(){}

Q_SIGNALS:
    void progress(int);
    void stateChanged(EvJob::State);

protected:
    void setMode(Mode);

private:
    friend class EvJobsManager;

    Mode m_mode;

};

#endif // EVJOB_H

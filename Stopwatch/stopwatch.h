#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject
{
    Q_OBJECT
public:
    explicit Stopwatch(QObject *parent = nullptr);


signals:
    void updateTime(int time);

public slots:
    void start();
    void stop();
    void reset();
    QString getPreviousLapTime();
    void updateTime();

private:
    QTimer timer;
    int startTime;
    int elapsedTime;
    bool running;
    int previousLapTime;
};

#endif // STOPWATCH_H

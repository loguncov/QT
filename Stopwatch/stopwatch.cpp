#include "stopwatch.h"
#include <QDateTime>

Stopwatch::Stopwatch(QObject *parent) : QObject(parent), running(false), startTime(0), elapsedTime(0), previousLapTime(0)
{
}

void Stopwatch::start()
{
    if (!running) {
        startTime = QDateTime::currentMSecsSinceEpoch() - elapsedTime;
        running = true;
        timer.start();
    }
}

void Stopwatch::stop()
{
    if (running) {
        elapsedTime = QDateTime::currentMSecsSinceEpoch() - startTime;
        running = false;
        timer.stop();
    }
}

void Stopwatch::reset()
{
    elapsedTime = 0;
    previousLapTime = 0;
    if (!running) {
        startTime = 0;
    } else {
        startTime = QDateTime::currentMSecsSinceEpoch();
    }
}

QString Stopwatch::getPreviousLapTime()
{
    QString lapTimeString = QString::number(previousLapTime / 1000.0, 'f', 2);
    return lapTimeString;
}

void Stopwatch::updateTime()
{
    int currentTime = QDateTime::currentMSecsSinceEpoch();
    int diff = currentTime - startTime;
    emit updateTime(diff / 1000);
    if (running) {
        previousLapTime = diff;
    }
}

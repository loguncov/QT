#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);

    // Устанавливаем соединение сигнала QTimer::timeout с слотом setTime
    QObject::connect(timer, &QTimer::timeout, this, &Stopwatch::setTime);
}

Stopwatch::~Stopwatch()
{
    // Деструктор класса Stopwatch
}

void Stopwatch::ToggleStopwatch()
{
    // Метод для включения и выключения секундомера

    if (timer->isActive())
    {
        timer->stop(); // Останавливаем таймер, если он активен
    }
    else
    {
        timer->start(100); // Запускаем таймер с интервалом 100 миллисекунд
    }
    emit sig_SendToggleSig(); // Генерируем сигнал для оповещения о переключении
}

void Stopwatch::ResetStopwatch()
{
    // Метод сброса секундомера

    time = 0; // Сбрасываем текущее время
    time_lap = 0; // Сбрасываем время для круга
    laps_count = 0; // Сбрасываем количество кругов
    time_lap_prev = 0; // Сбрасываем предыдущее время круга
    emit sig_SendResetSig(); // Генерируем сигнал для оповещения о сбросе
}

void Stopwatch::RecordLapTime()
{
    // Метод для записи времени текущего круга

    ++laps_count; // Увеличиваем счетчик кругов
    time_lap = time; // Запоминаем текущее время как время текущего круга
    emit sig_SendRecLapTimeSig(); // Генерируем сигнал для оповещения о записи времени круга
}

size_t Stopwatch::getLapsCount()
{
    // Метод для получения количества кругов
    return laps_count;
}

void Stopwatch::setTime()
{
    // Метод для обновления времени секундомера

    time += 100; // Увеличиваем текущее время на 100 миллисекунд
    emit sig_TimerChanged(); // Генерируем сигнал для оповещения об изменении времени
}

QString Stopwatch::c_str(const unsigned int& time)
{
    // Метод для форматирования времени в виде строки

    std::chrono::milliseconds ms(time);
    std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
    ms -= std::chrono::duration_cast<std::chrono::milliseconds>(s);
    std::chrono::minutes m = std::chrono::duration_cast<std::chrono::minutes>(ms);
    s -= std::chrono::duration_cast<std::chrono::seconds>(ms);
    return QString::number(m.count()) + ":" + QString::number(s.count()) + "." + QString::number(ms.count() / 100);
}

unsigned int Stopwatch::getTime()
{
    // Метод для получения текущего времени
    return time;
}

unsigned int Stopwatch::getLastLapTime()
{
    // Метод для получения времени последнего круга

    double new_lap = time_lap - time_lap_prev;
    time_lap_prev += new_lap; // Обновляем предыдущее время круга
    return new_lap; // Возвращаем время последнего круга
}

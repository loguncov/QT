#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pb_send_datagram->setText("Отправить датаграмму");

    udpWorker = new UDPworker(this); // Создаем объект UDPworker
    udpWorker->InitSocket(); // Инициализируем UDP сокет

    // Устанавливаем соединения (связи) сигналов и слотов для обработки данных от UDPworker
    connect(udpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);
    connect(udpWorker, &UDPworker::sig_sendInputToGUI, this, &MainWindow::DisplayInput);

    timer = new QTimer(this);
    // Устанавливаем связь для выполнения кода при каждом таймауте таймера
    connect(timer, &QTimer::timeout, this, [&]{
        QDateTime dateTime = QDateTime::currentDateTime();
        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);
        outStr << dateTime; // Записываем текущее время в байтовый массив
        udpWorker->SendDatagram(dataToSend); // Отправляем датаграмму
        timer->start(TIMER_DELAY); // Запускаем таймер снова
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Обработчик кнопки "Старт"
void MainWindow::on_pb_start_clicked()
{
    timer->start(TIMER_DELAY); // Запускаем таймер с интервалом TIMER_DELAY
}

// Метод для отображения входных данных
void MainWindow::DisplayInput(QString input, QString sender_ip)
{
    counterPck++; // Увеличиваем счетчик принятых пакетов
    if (counterPck % 20 == 0) {
        ui->te_result->clear(); // Очищаем текстовое поле каждые 20 пакетов
    }

    int size_bytes = input.toUtf8().size();

    QString str = "Принято " + input + " от " + sender_ip + ", размер сообщения(байт) " + QString::number(size_bytes);

    ui->te_result->append(str); // Добавляем информацию в текстовое поле
}

// Метод для отображения времени
void MainWindow::DisplayTime(QDateTime data)
{
    counterPck++; // Увеличиваем счетчик принятых пакетов
    if (counterPck % 20 == 0) {
        ui->te_result->clear(); // Очищаем текстовое поле каждые 20 пакетов
    }

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));
}

// Обработчик кнопки "Стоп"
void MainWindow::on_pb_stop_clicked()
{
    timer->stop(); // Останавливаем таймер
}

// Обработчик кнопки "Отправить датаграмму"
void MainWindow::on_pb_send_datagram_clicked()
{
    QString input = ui->le_datagram->text();
    QByteArray input_byte_data;
    QDataStream input_str(&input_byte_data, QIODevice::WriteOnly);

    input_str << input; // Записываем введенные данные в байтовый массив

    udpWorker->SendInputDatagram(input_byte_data); // Отправляем введенные данные как датаграмму
}

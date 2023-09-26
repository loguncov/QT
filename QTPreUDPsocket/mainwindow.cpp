#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpWorker->InitSocket();

    connect(udpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);
    // Связывание сигнала нажатия на кнопку с методом sendDatagram
    connect(ui->pb_send, &QPushButton::clicked, this, &MainWindow::sendDatagram);
    // Связывание сигнала из udpWorker с методом MainWindow
    connect(udpWorker, &UDPworker::sig_sendReceivedData, this, &MainWindow::updateReceivedData);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{

        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

        outStr << dateTime;

        udpWorker->SendDatagram(dataToSend);
        timer->start(TIMER_DELAY);

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_start_clicked()
{
    timer->start(TIMER_DELAY);
}


void MainWindow::DisplayTime(QDateTime data)
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));


}

void MainWindow::sendDatagram() {
    QString textToSend = ui->lineEdit->text().toUtf8();  // Получаем текст из QLineEdit
    QByteArray dataToSend = textToSend.toUtf8();  // Преобразуем текст в массив байт

    // Отправляем датаграмму на localhost и порт BIND_PORT
    udpWorker->SendDatagram(dataToSend);

    // Очищаем QLineEdit после отправки
    ui->lineEdit->clear();
}

void MainWindow::updateReceivedData(const QString& senderAddress, int messageSize) {
    ui->te_result->append(QString("Принято сообщение от адреса %1, размер сообщения (байт): %2").arg(senderAddress).arg(messageSize));
}






void MainWindow::on_pb_stop_clicked()
{
    timer->stop();
}


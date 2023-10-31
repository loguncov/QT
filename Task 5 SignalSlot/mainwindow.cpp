#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stopwatch = new Stopwatch(this); // Создаем объект секундомера

    RsvResetSig(); // Вызываем метод сброса сигналов
    ui->pb_start_stop->setText("Старт"); // Устанавливаем текст кнопки "Старт"
    ui->pb_start_stop->setCheckable(true); // Делаем кнопку "Старт" чекабельной
    ui->pb_lap->setText("Круг"); // Устанавливаем текст кнопки "Круг"
    ui->pb_lap->setDisabled(true); // Отключаем кнопку "Круг"
    ui->pb_reset->setText("Очистить"); // Устанавливаем текст кнопки "Очистить"

    // Устанавливаем соединения между сигналами объекта Stopwatch и слотами класса MainWindow
    QObject::connect(stopwatch, &Stopwatch::sig_TimerChanged, this, &MainWindow::RsvUpdateSig);
    QObject::connect(stopwatch, &Stopwatch::sig_SendToggleSig, this, &MainWindow::RsvToggleSig);
    QObject::connect(stopwatch, &Stopwatch::sig_SendResetSig, this, &MainWindow::RsvResetSig);
    QObject::connect(stopwatch, &Stopwatch::sig_SendRecLapTimeSig, this, &MainWindow::RsvRecLapTimeSig);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RsvUpdateSig()
{
    ui->lb_output->setText(stopwatch->c_str(stopwatch->getTime())); // Обновляем текстовую метку с текущим временем
}

void MainWindow::RsvToggleSig()
{
    if (ui->pb_start_stop->isChecked())
    {
        ui->pb_start_stop->setText("Стоп"); // Устанавливаем текст кнопки "Стоп" при включении
        ui->pb_lap->setDisabled(false); // Разблокируем кнопку "Круг" при включении
    }
    else
    {
        ui->pb_start_stop->setText("Старт"); // Устанавливаем текст кнопки "Старт" при выключении
        ui->pb_lap->setDisabled(true); // Отключаем кнопку "Круг" при выключении
    }
}

void MainWindow::RsvResetSig()
{
    ui->lb_output->setText("0:0.0"); // Сбрасываем текстовую метку на "0:0.0"
}

void MainWindow::RsvRecLapTimeSig()
{
    ui->tb_logs->append("Круг " + QString::number(stopwatch->getLapsCount()) + ", время: " + stopwatch->c_str(stopwatch->getLastLapTime()) + " сек."); // Добавляем запись о круге в текстовое поле
}

void MainWindow::on_pb_start_stop_toggled(bool checked)
{
    stopwatch->ToggleStopwatch(); // Обработка переключения кнопки "Старт/Стоп"
}

void MainWindow::on_pb_reset_clicked()
{
    stopwatch->ResetStopwatch(); // Обработка нажатия кнопки "Очистить"
}

void MainWindow::on_pb_lap_clicked()
{
    stopwatch->RecordLapTime(); // Обработка нажатия кнопки "Круг"
}

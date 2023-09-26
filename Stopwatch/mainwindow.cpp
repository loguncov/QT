#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    running = false;
    roundCount = 0;

    connect(ui->startStopButton, &QPushButton::clicked, this, &MainWindow::startStopClicked);
    connect(ui->roundButton, &QPushButton::clicked, this, &MainWindow::roundClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::clearClicked);

    connect(&timer, &QTimer::timeout, this, &MainWindow::updateTimer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startStopClicked()
{
    if (running) {
        ui->startStopButton->setText("Старт");
        timer.stop();
    } else {
        ui->startStopButton->setText("Стоп");
        timer.start(100); // обновление каждые 0.1 секунды
    }
    running = !running;
}

void MainWindow::updateTimer()
{
    time = time.addMSecs(100);
    ui->timeLabel->setText(time.toString("hh:mm:ss.zzz"));
}

void MainWindow::roundClicked()
{
    if (running) {
        roundCount++;
        QTime roundTime = time.addMSecs(-100);
        ui->roundBrowser->append(QString("Круг %1, время: %2 сек").arg(roundCount).arg(roundTime.toString("ss.zzz")));
    }
}

void MainWindow::clearClicked()
{
    timer.stop();
    running = false;
    time = QTime(0, 0);
    roundCount = 0;
    ui->timeLabel->clear();
    ui->roundBrowser->clear();
    ui->startStopButton->setText("Старт");
}

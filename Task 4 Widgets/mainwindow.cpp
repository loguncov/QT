#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Назначение имен RadioButton
    ui->radioButton1->setText("RadioButton 1");
    ui->radioButton2->setText("RadioButton 2");

    // Добавление элементов в выпадающий список
    for (int i = 1; i <= 10; ++i) {
        ui->comboBox->addItem("Item " + QString::number(i));
    }

    // Изменение надписи и типа кнопки
    ui->pushButton->setText("Toggle Button");
    ui->pushButton->setCheckable(true);

    // Установка начальных значений прогресс-бара
    ui->progressBar->setRange(0, 10);
    ui->progressBar->setValue(0);

    // Подключение обработчика нажатия на кнопку
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onPushButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPushButtonClicked()
{
    static int progressValue = 0; // Статическая переменная для отслеживания прогресса

    if (ui->pushButton->isChecked()) {
        progressValue += 1;
        ui->progressBar->setValue(progressValue);

        if (progressValue > 10) {
            progressValue = 0;
            ui->progressBar->setValue(progressValue);
        }
    }
}

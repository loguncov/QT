#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sb_initNum->setValue(200000); // Устанавливаем начальное значение в элементе управления "sb_initNum"
    ui->rb_synchOff->setChecked(true); // Устанавливаем начальное состояние кнопки "rb_synchOff"

    // Создаем объекты классов Controller и ExampleRace
    race1 = new Controller(&m);
    race2 = new Controller(&m);
    concurRace1 = new ExampleRace(&m);
    concurRace2 = new ExampleRace(&m);

    // Устанавливаем соединения (связи) сигналов и слотов
    // для обработки завершения работы потоков
    connect(race1, &Controller::sig_WorkFinish, [&](){
        // Отображаем информацию только после завершения второго потока
        if(countFinish == 0){
            countFinish++;
        }
        else{
            ui->te_debug->append("Искомое число равно: " + QString::number(number) + ", а должно быть " +
                                  QString::number(ui->sb_initNum->value() * 2));
            ui->pb_start->setEnabled(true);
        }
    });

    connect(race2, &Controller::sig_WorkFinish, [&](){
        if(countFinish == 0){
            countFinish++;
        }
        else{
            ui->te_debug->append("Искомое число равно: " + QString::number(number) + ", а должно быть " +
                                 QString::number(ui->sb_initNum->value() * 2));
            ui->pb_start->setEnabled(true);
        }
    });

    connect(concurRace1, &ExampleRace::sig_Finish, [&](){
        if(countFinish == 0){
            countFinish++;
        }
        else{
            ui->te_debug->append("Искомое число равно: " + QString::number(number) + ", а должно быть " +
                                 QString::number(ui->sb_initNum->value() * 2));
            ui->pb_start->setEnabled(true);
        }
    });

    connect(concurRace2, &ExampleRace::sig_Finish, [&](){
        if(countFinish == 0){
            countFinish++;
        }
        else{
            ui->te_debug->append("Искомое число равно: " + QString::number(number) + ", а должно быть " +
                                 QString::number(ui->sb_initNum->value() * 2));
            ui->pb_start->setEnabled(true);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Метод запускает два потока
void MainWindow::StartRace(void)
{
    if(ui->rb_qtConcur->isChecked()){
        // Если выбран режим QtConcurrent
        // Создаем лямбда-функции для выполнения в двух потоках
        auto race1 = [&](){
            return concurRace1->DoWork(&number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value());
        };
        auto race2 = [&](){
            return concurRace2->DoWork(&number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value());
        };
        // Запускаем выполнение лямбда-функций в параллельных потоках
        QtConcurrent::run(race1).then(race2);
    }
    else{
        // Если выбран режим без QtConcurrent
        race1->operate(&number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value());
        race2->operate(&number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value());
    }
}

// Обработка кнопки "Старт"
void MainWindow::on_pb_start_clicked()
{
    ui->pb_start->setEnabled(false);
    countFinish = 0;
    number = 0;
    StartRace();
}

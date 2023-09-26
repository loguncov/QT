#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startStopClicked();
    void roundClicked();
    void clearClicked();
    void updateTimer();

private:
    Ui::MainWindow *ui;
    bool running;
    int roundCount;
    QTime time;
};

#endif // MAINWINDOW_H

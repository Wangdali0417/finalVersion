#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "worker.h"
#include "widget.h"
#include "global.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread workerThread;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();

    void on_runButton_clicked();
    void showText(const QString &str);
    void cont();

private:
    Ui::MainWindow *ui;

    Worker *wk;
    Widget *w ;
};

#endif // MAINWINDOW_H

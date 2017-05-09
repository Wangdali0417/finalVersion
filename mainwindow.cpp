#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
//test for git

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wk = new Worker();
    ui->widget = new Widget();
    wk->moveToThread(&workerThread);
    QObject::connect(&workerThread, SIGNAL(finished()), wk, SLOT(deleteLater()));
    QObject::connect(wk, SIGNAL(changeFlagComp()), ui->widget, SLOT(changeFlagComp()));
    QObject::connect(wk, SIGNAL(showText(QString)), this, SLOT(showText(QString)));
    QObject::connect(wk, SIGNAL(cont()), this, SLOT(cont()));
    workerThread.start();
    //Timer initialS
    QObject::connect(wk, SIGNAL(plot()), &ui->widget->m_timer, SLOT(start()));
}

MainWindow::~MainWindow()
{
    workerThread.quit();
    workerThread.wait();
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    wk->doWork();
}

void MainWindow::on_runButton_clicked()
{
    w->changeFlag();
}

void MainWindow::showText(const QString &str)
{
    ui->MainTextBrowser->append(str);
}

void MainWindow::cont()
{
    ui->runButton->setHidden(false);

}

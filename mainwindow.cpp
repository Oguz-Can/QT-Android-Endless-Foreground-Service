#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->show();
    connect(&LocalLogger, &BUdpReception::onLog, this, &MainWindow::logReceived);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{

    QAndroidJniObject::callStaticMethod<void>("com/service/classes/MyService",
                                             "startMyService",
                                             "(Landroid/content/Context;)V",
                                              QtAndroid::androidActivity().object());
}

void MainWindow::on_stopButton_clicked()
{
    QAndroidJniObject::callStaticMethod<void>("com/service/classes/MyService",
                                             "stopMyService",
                                             "(Landroid/content/Context;)V",
                                              QtAndroid::androidActivity().object());
}

void MainWindow::logReceived(QString log){
    qDebug() << log;
    ui->textBrowser->append(log);
}

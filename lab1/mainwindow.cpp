#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->wrongPassAlert->setVisible(false);

    passList = new PassListWindow;
    connect(this, SIGNAL(check_pass(QString)), passList, SLOT(check_pass(QString)));
    connect(passList, SIGNAL(pageSwap(bool)), this, SLOT(pageSwap(bool)));
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::pageSwap(bool isCorrect) {
    if (isCorrect) {
        this->close();
        passList->show();
    } else {
        ui->wrongPassAlert->setVisible(true);
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString pass = ui->passEnterLine->text();
    emit check_pass(pass);
}


void MainWindow::on_passEnterLine_textChanged()
{
    ui->wrongPassAlert->setVisible(false);
}


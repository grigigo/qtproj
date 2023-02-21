#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->wrongPassAlert->setVisible(false);

    passList = new PassListWindow;
    connect (passList, &PassListWindow::passListSign, this, &MainWindow::show);
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::authorize(QString password) {
    QString truePass = "qwerty";
    return truePass == password;
}

void MainWindow::on_pushButton_clicked()
{
    QString pass = ui->passEnterLine->text();
    if (authorize(pass)) {
        this->close();
        passList->show();
    } else {
        ui->wrongPassAlert->setVisible(true);
    }
}


void MainWindow::on_passEnterLine_textChanged()
{
    ui->wrongPassAlert->setVisible(false);
}


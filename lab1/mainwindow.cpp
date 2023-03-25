#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);
    ui->wrongPassAlert->setVisible(false);
    ui->debuggerPresentButton->setVisible(false);

    m_antidebug_timer.setInterval(1000);
    connect(&m_antidebug_timer, &QTimer::timeout, this, &MainWindow::antidebug_timer);
    m_antidebug_timer.start();

    passList = new PassListWindow;
    connect(this, SIGNAL(check_pass(QString)), passList, SLOT(check_pass(QString)));
    connect(passList, SIGNAL(pageSwap(bool)), this, SLOT(pageSwap(bool)));
}

void MainWindow::antidebug_timer() {
    if (IsDebuggerPresent()) {
        ui->debuggerPresentButton->setVisible(true);
    }
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


void MainWindow::on_pushButton_clicked() {
    QString pass = ui->passEnterLine->text();
    emit check_pass(pass);
}


void MainWindow::on_passEnterLine_textChanged() {
    ui->wrongPassAlert->setVisible(false);
}


void MainWindow::on_debuggerPresentButton_clicked() {
    QApplication::quit();
}


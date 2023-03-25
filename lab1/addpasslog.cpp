#include "addpasslog.h"
#include "ui_addpasslog.h"

addPassLog::addPassLog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addPassLog)
{
    ui->setupUi(this);
}

addPassLog::~addPassLog()
{
    delete ui;
}

void addPassLog::on_addBtn_clicked() {
    QString login = ui->loginLineEdit->text();
    QString pass = ui->passLineEdit->text();
    QString url = ui->urlLineEdit->text();
    QString logpass = "{"
                      "\n\t\"login\":" + login + ","
                      "\n\t\"password\":" + pass +
                      "}";
    qDebug() << logpass;

    this->close();
    //passListSignal(url, logpass);
}


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

void addPassLog::on_addBtn_clicked()
{
    QFile file;
    file.setFileName("../lab1/test.json");
    file.open(QIODevice::WriteOnly);

    QJsonObject test;
    test.insert("url", ui->urlLineEdit->text());
    test.insert("login", ui->loginLineEdit->text());
    test.insert("pass", ui->passLineEdit->text());

    file.close();
    passListSignal(test);
    this->close();
    toPassList();
}


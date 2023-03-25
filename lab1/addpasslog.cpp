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
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("login", ui->loginLineEdit->text());
    obj.insert("pass", ui->passLineEdit->text());
    doc.setObject(obj);

    QString url = ui->urlLineEdit->text();

    this->close();
    passListSignal(url, doc.toJson());
}


#include "passlistwindow.h"
#include "ui_passlistwindow.h"
#include <QDebug>

PassListWindow::PassListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PassListWindow) {

    ui->setupUi(this);

    addpasslog = new addPassLog;
    connect(addpasslog, SIGNAL(passListSignal(QString, QString)), this, SLOT(passListSignal(QString, QString)));

    clipboard = QApplication::clipboard();

    connect(ui->tablePassLog, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));
}

void PassListWindow::check_pass(QString pass) {
    QByteArray hash = QCryptographicHash::hash(pass.toUtf8(), QCryptographicHash::Sha256);

    hex_hash = hash.toHex();
    cridentials = CryptoController::decrypt_file("../lab1/cridentials.enc", hex_hash);

    createPassTable("");
    emit pageSwap(true);
}

void PassListWindow::createPassTable(QString search_line) {
    ui->tablePassLog->setRowCount(0);
    ui->tablePassLog->setColumnCount(3);
    ui->tablePassLog->setHorizontalHeaderItem(0, new QTableWidgetItem("Url"));
    ui->tablePassLog->setHorizontalHeaderItem(1, new QTableWidgetItem("Login"));
    ui->tablePassLog->setHorizontalHeaderItem(2, new QTableWidgetItem("Password"));

    if (cridentials) {
        for (auto record : *cridentials) {
            if (((QString)record.site).contains(search_line)) {
                ui->tablePassLog->insertRow(ui->tablePassLog->rowCount());

                QTableWidgetItem *item = new QTableWidgetItem;
                item->setText("        " + (QString)record.site + "        ");
                item->setData(Qt::UserRole, record.site);
                item->setTextAlignment(Qt::AlignCenter);
                ui->tablePassLog->setItem(ui->tablePassLog->rowCount()-1, 0, item);

                item = new QTableWidgetItem;
                item->setText("•••••••");
                item->setData(Qt::UserRole, "login");
                item->setTextAlignment(Qt::AlignCenter);
                ui->tablePassLog->setItem(ui->tablePassLog->rowCount()-1, 1, item);

                item = new QTableWidgetItem;
                item->setText("•••••••");
                item->setData(Qt::UserRole, "password");
                item->setTextAlignment(Qt::AlignCenter);
                ui->tablePassLog->setItem(ui->tablePassLog->rowCount()-1, 2, item);
            }
        }
    }
    ui->tablePassLog->resizeRowsToContents();
    ui->tablePassLog->resizeColumnsToContents();
}

void PassListWindow::onTableClicked(const QModelIndex &index) {
    clipboard->setText(CryptoController::decrypt_record(cridentials->toList()[index.row()].encrypted, index.data(Qt::UserRole).toString(), hex_hash));
}

PassListWindow::~PassListWindow() {
    delete ui;
}

void PassListWindow::on_searchButton_clicked() {
    QString searchText = ui->searchLine->text();
    ui->tablePassLog->clear();

    /*
    QFile file;
    file.setFileName("../lab1/test.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString text = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8());
    */

    createPassTable(searchText);
}

void PassListWindow::on_addElemBtn_clicked() {
    this->close();
    addpasslog->show();
}

void PassListWindow::passListSignal(QString url, QString obj) {
    this->show();

    QString encrypted_logpass = CryptoController::encrypt_login_password(obj, hex_hash);
    /*
    QFile file;
    file.setFileName("../lab1/test.json");
    file.open(QIODevice::WriteOnly);


    QJsonArray array = doc.object().value("list").toArray();
    QJsonObject obj;
    array.append(elem);
    obj.insert("list", array);
    doc.setObject(obj);

    file.write(doc.toJson());
    file.close();

    qWarning() << doc;
    */
    createPassTable("");
}


void PassListWindow::on_tablePassLog_cellDoubleClicked(int row, int column) {
    /*
    QFile file;
    file.setFileName("../lab1/test.json");
    file.open(QIODevice::WriteOnly);

    QJsonArray array = doc.object().value("list").toArray();
    QJsonObject obj;

    QString test = ui->tablePassLog->takeItem(row, column)->data(Qt::UserRole).toString();
    for (int i = 0; i < doc.object().value("list").toArray().size(); ++i) {
        if (array[i].toObject().value("url") == test) {
            array.removeAt(i);
        }
    }
    qWarning() << array;

    obj.insert("list", array);
    doc.setObject(obj);

    file.write(doc.toJson());
    file.close();
    ui->tablePassLog->removeRow(row);
    */
}


#include "passlistwindow.h"
#include "ui_passlistwindow.h"
#include <QDebug>

PassListWindow::PassListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PassListWindow) {

    ui->setupUi(this);

    addpasslog = new addPassLog;
    connect(addpasslog, SIGNAL(passListSignal(QString, QByteArray)), this, SLOT(passListSignal(QString, QByteArray)));

    clipboard = QApplication::clipboard();

    connect(ui->tablePassLog, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));
}

void PassListWindow::check_pass(QString pass) {
    QByteArray hash = QCryptographicHash::hash(pass.toUtf8(), QCryptographicHash::Sha256);

    hex_hash = hash.toHex();
    cridentials = CryptoController::decrypt_file(filename, hex_hash);

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
                item->setData(Qt::UserRole, (QString)record.site);
                item->setTextAlignment(Qt::AlignCenter);
                ui->tablePassLog->setItem(ui->tablePassLog->rowCount()-1, 0, item);

                item = new QTableWidgetItem;
                item->setText("  •••••••  ");
                item->setData(Qt::UserRole, "login");
                item->setTextAlignment(Qt::AlignCenter);
                ui->tablePassLog->setItem(ui->tablePassLog->rowCount()-1, 1, item);

                item = new QTableWidgetItem;
                item->setText("  •••••••  ");
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
    if (index.column() != 0) {
        clipboard->setText(CryptoController::decrypt_record(cridentials->toList()[index.row()].encrypted, index.data(Qt::UserRole).toString(), hex_hash));
    } else {
        clipboard->setText(index.data(Qt::UserRole).toString());
    }
}

PassListWindow::~PassListWindow() {
    delete ui;
}

void PassListWindow::on_searchButton_clicked() {
    QString searchText = ui->searchLine->text();
    ui->tablePassLog->clear();

    createPassTable(searchText);
}

void PassListWindow::on_addElemBtn_clicked() {
    this->close();
    addpasslog->show();
}

void PassListWindow::passListSignal(QString url, QByteArray logpass) {
    this->show();

    QByteArray encrypted_logpass = CryptoController::encrypt_login_password(logpass, hex_hash);
    Cridentials new_record;
    new_record.site = url.toUtf8();
    new_record.encrypted = encrypted_logpass;
    cridentials->append(new_record);

    QJsonDocument doc;
    QJsonArray array;
    for (auto item : *cridentials) {
        QJsonObject record;
        record.insert("url", item.site.data());
        record.insert("logpass", item.encrypted.data());
        array.append(record);
    }
    QJsonObject list;
    list.insert("list", array);
    doc.setObject(list);

    if (CryptoController::encrypt_file(doc.toJson(), filename, hex_hash)) {
        createPassTable("");
    } else {
        return;
    }

}


void PassListWindow::on_tablePassLog_cellDoubleClicked(int row, int column) {
    cridentials->removeAt(row);

    QJsonDocument doc;
    QJsonArray array;
    for (auto item : *cridentials) {
        QJsonObject record;
        record.insert("url", item.site.data());
        record.insert("logpass", item.encrypted.data());
        array.append(record);
    }
    QJsonObject list;
    list.insert("list", array);
    doc.setObject(list);

    if (CryptoController::encrypt_file(doc.toJson(), filename, hex_hash)) {
        createPassTable("");
    } else {
        return;
    }

    ui->tablePassLog->removeRow(row);
}


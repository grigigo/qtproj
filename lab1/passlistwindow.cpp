#include "passlistwindow.h"
#include "ui_passlistwindow.h"

PassListWindow::PassListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PassListWindow)
{
    ui->setupUi(this);

    addpasslog = new addPassLog;
    connect(addpasslog, SIGNAL(passListSignal(const QJsonObject &)), this, SLOT(addElem(const QJsonObject &)));
    connect(addpasslog, &addPassLog::toPassList, this, &PassListWindow::show);

    QClipboard *clipboard = QApplication::clipboard();

    QFile file;
    file.setFileName("../lab1/test.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString text = file.readAll();
    file.close();

    doc = QJsonDocument::fromJson(text.toUtf8());

    //QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8());

    createPassTable(doc, "");

    ui->tablePassLog->resizeRowsToContents();
    ui->tablePassLog->resizeColumnsToContents();

    file.open(QIODevice::WriteOnly);
    QJsonObject test1;
    test1.insert("url", "test@example");
    test1.insert("login", "user");
    test1.insert("pass", "password");

    QJsonObject test2;
    test2.insert("url", "test123@example");
    test2.insert("login", "user123");
    test2.insert("pass", "password123");

    QJsonArray array;


    QJsonObject final;
    array.append(test1);
    array.append(test2);

    QJsonDocument newDoc;
    final.insert("list", array);
    newDoc.setObject(final);
    file.write(newDoc.toJson());

    file.close();

    connect(ui->tablePassLog, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onTableClicked(const QModelIndex &)));
}

void PassListWindow::createPassTable(QJsonDocument d, QString search_line) {
    ui->tablePassLog->setRowCount(0);
    ui->tablePassLog->setColumnCount(3);
    ui->tablePassLog->setHorizontalHeaderItem(0, new QTableWidgetItem("Url"));
    ui->tablePassLog->setHorizontalHeaderItem(1, new QTableWidgetItem("Login"));
    ui->tablePassLog->setHorizontalHeaderItem(2, new QTableWidgetItem("Password"));
    for (int i = 0; i < d.object().value("list").toArray().size(); ++i) {
        if (d.object().value("list").toArray()[i].toObject().value("url").toString().contains(search_line)) {
            ui->tablePassLog->insertRow(ui->tablePassLog->rowCount());

            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText("        " + d.object().value("list").toArray()[i].toObject().value("url").toString() + "        ");
            item->setData(Qt::UserRole, d.object().value("list").toArray()[i].toObject().value("url").toString());
            item->setTextAlignment(Qt::AlignCenter);
            ui->tablePassLog->setItem(ui->tablePassLog->rowCount()-1, 0, item);

            item = new QTableWidgetItem;
            item->setText("        " + createButton(d.object().value("list").toArray()[i].toObject().value("login").toString()) + "        ");
            item->setData(Qt::UserRole, d.object().value("list").toArray()[i].toObject().value("login").toString());
            item->setTextAlignment(Qt::AlignCenter);
            ui->tablePassLog->setItem(ui->tablePassLog->rowCount()-1, 1, item);

            item = new QTableWidgetItem;
            item->setText("        " + createButton(d.object().value("list").toArray()[i].toObject().value("pass").toString()) + "        ");
            item->setData(Qt::UserRole, d.object().value("list").toArray()[i].toObject().value("pass").toString());
            item->setTextAlignment(Qt::AlignCenter);
            ui->tablePassLog->setItem(ui->tablePassLog->rowCount()-1, 2, item);
        }
    }
}

void PassListWindow::onTableClicked(const QModelIndex &index) {
    clipboard->setText(index.data(Qt::UserRole).toString());
}

QString PassListWindow::createButton(QString text) {
    QString dots = "";
    for (int i = 0; i < text.length(); ++i) {
        dots += "*";
    }
    return dots;
}

PassListWindow::~PassListWindow()
{
    delete ui;
}

void PassListWindow::on_searchButton_clicked()
{
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

    createPassTable(doc, searchText);
}

void PassListWindow::on_addElemBtn_clicked()
{
    this->close();
    addpasslog->show();
}

void PassListWindow::addElem(const QJsonObject &elem) {
    QFile file;
    file.setFileName("../lab1/test.json");
    file.open(QIODevice::WriteOnly);

    QJsonArray array = doc.object().value("list").toArray();
    qWarning() << doc.object().value("list").toArray();
    qWarning() << array;
    QJsonObject obj;

    array.append(elem);
    qWarning() << array;
    obj.insert("list", array);
    doc.setObject(obj);
    file.write(doc.toJson());
    file.close();

    createPassTable(doc, "");
}


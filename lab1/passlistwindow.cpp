#include "passlistwindow.h"
#include "ui_passlistwindow.h"

PassListWindow::PassListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PassListWindow)
{
    ui->setupUi(this);

    QClipboard *clipboard = QApplication::clipboard();

    QPushButton *button = new QPushButton(tr("Copy!"));
    connect(button, &QPushButton::clicked, this, &PassListWindow::on_multiplyButton_clicked);

    QFile file;
    file.setFileName("../lab1/test.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text); //WriteOnly
    QString text = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(text.toUtf8());
    qWarning() << d << "\n";
    qWarning() << d.object().value("list").toArray() << "\n";
    qWarning() << d.object().value("list").toArray().size() << "\n";

    for (int i = 0; i < d.object().value("list").toArray().size(); ++i) {
        //qWarning() << d.object().value("list").toArray()[i].toObject();
        createListElem(d.object().value("list").toArray()[i].toObject());
    }

    qWarning() << "";

    file.setFileName("../lab1/test.json");
    file.open(QIODevice::WriteOnly);

    QJsonArray array;
    QJsonObject final;

    QJsonObject test1;
    test1.insert("mail", "123@example.com");
    test1.insert("login", "user1");
    test1.insert("pass", "qwerty");

    QJsonObject test2;
    test2.insert("mail", "456@example.com");
    test2.insert("login", "user2");
    test2.insert("pass", "password");


    array.append(test1);
    array.append(test2);
    final.insert("list", array);

    qWarning() << array << "\n";

    QJsonDocument jsonDoc;
    jsonDoc.setObject(final);
    file.write(jsonDoc.toJson());
    file.close();

}

void PassListWindow::on_multiplyButton_clicked() {
    //button.objectName();
    //self.pushButton_9_3.objectName()
    QPushButton *btn = qobject_cast<QPushButton *>(sender());
    clipboard->setText(btn->accessibleName());
}

void PassListWindow::createListElem(QJsonObject elem) {
    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    ui->layoutList->addLayout(buttonsLayout);
    qWarning() << elem;

    /*
    QLineEdit *lineEdit = new QLineEdit(tr("mail%1").arg(ui->layoutList->count()));
    lineEdit->setEchoMode(QLineEdit::Password);
    lineEdit->setReadOnly(true);
    lineEdit->setText(elem.value("mail").toString());
    buttonsLayout->addWidget(lineEdit);
    lineEdit = new QLineEdit(tr("login%1").arg(ui->layoutList->count()));
    lineEdit->setEchoMode(QLineEdit::Password);
    lineEdit->setReadOnly(true);
    lineEdit->setText(elem.value("login").toString());
    buttonsLayout->addWidget(lineEdit);
    lineEdit = new QLineEdit(tr("password%1").arg(ui->layoutList->count()));
    lineEdit->setEchoMode(QLineEdit::Password);
    lineEdit->setReadOnly(true);
    lineEdit->setText(elem.value("pass").toString());
    buttonsLayout->addWidget(lineEdit);
    */

    QPushButton *lineEdit = new QPushButton;
    lineEdit->setAccessibleName(elem.value("mail").toString());
    connect(lineEdit, SIGNAL(clicked()), this, SLOT(on_multiplyButton_clicked()));
    lineEdit->setText(createButton(elem.value("mail").toString()));
    lineEdit->setFlat(true);
    buttonsLayout->addWidget(lineEdit);
    lineEdit = new QPushButton;
    lineEdit->setAccessibleName(elem.value("login").toString());
    connect(lineEdit, SIGNAL(clicked()), this, SLOT(on_multiplyButton_clicked()));
    lineEdit->setText(createButton(elem.value("login").toString()));
    lineEdit->setFlat(true);
    buttonsLayout->addWidget(lineEdit);
    lineEdit = new QPushButton;
    lineEdit->setAccessibleName(elem.value("pass").toString());
    connect(lineEdit, SIGNAL(clicked()), this, SLOT(on_multiplyButton_clicked()));
    lineEdit->setText(createButton(elem.value("pass").toString()));
    lineEdit->setFlat(true);
    buttonsLayout->addWidget(lineEdit);
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

#ifndef ADDPASSLOG_H
#define ADDPASSLOG_H

#include <QMainWindow>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QToolButton>
#include <QLineEdit>

namespace Ui {
class addPassLog;
}

class addPassLog : public QMainWindow
{
    Q_OBJECT

public:
    explicit addPassLog(QWidget *parent = nullptr);
    ~addPassLog();

private:
    Ui::addPassLog *ui;

signals:
    void toPassList();
    void passListSignal(const QJsonObject &obj);

private slots:
    void on_addBtn_clicked();
};

#endif // ADDPASSLOG_H

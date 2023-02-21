#ifndef PASSLISTWINDOW_H
#define PASSLISTWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QToolButton>
#include <QLineEdit>
#include <QClipboard>
#include <QTableWidgetItem>
#include <QTableWidget>
#include "addpasslog.h"

namespace Ui {
class PassListWindow;
}

class PassListWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PassListWindow(QWidget *parent = nullptr);
    ~PassListWindow();

private:
    Ui::PassListWindow *ui;
    QClipboard *clipboard;
    addPassLog *addpasslog;
    QJsonDocument doc;
    QString createButton(QString text);
    void createPassTable(QJsonDocument d, QString text);

private slots:
    void onTableClicked(const QModelIndex &index);
    void on_searchButton_clicked();
    void addElem(const QJsonObject &obj);
    void on_addElemBtn_clicked();

    void on_tablePassLog_cellDoubleClicked(int row);

signals:
    void passListSign();
};

#endif // PASSLISTWINDOW_H

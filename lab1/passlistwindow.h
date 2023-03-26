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
#include "cryptocontroller.h"
#include <QCryptographicHash>
#include <QList>

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
    void createPassTable(QString text);
    QList<Cridentials> * cridentials = nullptr;
    QByteArray hex_hash;
    QString filename = "C:\\programs\\qtproj\\lab1\\cridentials.enc";

public slots:
    void onTableClicked(const QModelIndex &index);
    void on_searchButton_clicked();
    void on_addElemBtn_clicked();
    void on_tablePassLog_cellDoubleClicked(int row, int column);
    void check_pass(QString pass);
    void passListSignal(QString url, QByteArray logpass);

signals:
    void pageSwap(bool isCorrect);
};

#endif // PASSLISTWINDOW_H

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
    void createListElem(QJsonObject elem);
    QString createButton(QString text);

private slots:
    void on_multiplyButton_clicked();

signals:
    void passListSign();
};

#endif // PASSLISTWINDOW_H

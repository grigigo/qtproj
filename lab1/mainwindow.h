#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "passlistwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    PassListWindow *passList;

public slots:
    void on_pushButton_clicked();
    void on_passEnterLine_textChanged();
    void pageSwap(bool isCorrect);

private:
    Ui::MainWindow *ui;

signals:
    void check_pass(QString pass);

};
#endif // MAINWINDOW_H

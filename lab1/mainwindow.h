#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <passlistwindow.h>

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

private slots:
    void on_pushButton_clicked();
    bool authorize(QString password);

    void on_wrongPassAlert_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

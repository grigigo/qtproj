#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "passlistwindow.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(bool checkresult, QWidget *parent = nullptr);
    ~MainWindow();
    PassListWindow *passList;

private:
    Ui::MainWindow *ui;
    QTimer m_antidebug_timer;
    void antidebug_timer();

signals:
    void check_pass(QString pass);

public slots:
    void on_pushButton_clicked();
    void on_passEnterLine_textChanged();
    void pageSwap(bool isCorrect);

private slots:
    void on_debuggerPresentButton_clicked();
    void on_modifyButton_clicked();
};
#endif // MAINWINDOW_H

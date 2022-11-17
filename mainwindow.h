#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QMessageBox>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "register1.h"
#include "choose.h"

//int user_id = 1;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sendData(QString);

private slots:
    void on_login_clicked();
    void on_register_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

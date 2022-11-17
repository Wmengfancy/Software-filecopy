#ifndef REGISTER1_H
#define REGISTER1_H

#include <QWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
//#include <QString>

namespace Ui {
class register1;
}

class register1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit register1(QWidget *parent = nullptr);
    ~register1();

private slots:
    void on_button_reg_clicked();

    void on_return_button_clicked();

private:
    Ui::register1 *ui;
};

#endif // REGISTER1_H

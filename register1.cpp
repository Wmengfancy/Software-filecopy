//注册功能

#include "register1.h"
#include "mainwindow.h"
#include "ui_register1.h"
#include <QString>
#include <QGraphicsDropShadowEffect>

register1::register1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::register1)
{
    ui->setupUi(this);

    QPixmap *pix = new QPixmap(":/girl1.png");
    QSize sz = ui->label_image->size();
    ui->label_image->setPixmap(pix->scaled(sz));

    connect(ui->button_reg,SIGNAL(clicked()),this,SLOT(on_button_reg_clicked()));
}

register1::~register1()
{
    delete ui;
}

void register1::on_button_reg_clicked()
{
    QString name_reg = ui->name_reg->text();
    QString password_reg = ui->password_reg->text();
    QString confirm_reg = ui->confirm_reg->text();

    if(name_reg=="")
        QMessageBox::warning(this,"","用户名不能为空");
    else if (password_reg=="" || confirm_reg=="")
        QMessageBox::warning(this,"","密码不能为空");
    else if (password_reg != confirm_reg)
        QMessageBox::warning(this,"","两次输入的密码不一致");
    else{
        QString name_sql = QString("select * from information where name='%1'" ).arg(name_reg);
        QSqlQuery query1;
        query1.exec(name_sql);
        if(query1.first())
        {
            //your name has been register!
        }
        else{
            QString command = QString("insert into information(name,password) values('%1','%2') ").arg(name_reg).arg(password_reg);
            QSqlQuery query;
            if(query.exec(command))
            {
                 QMessageBox::critical(this,"注册通知","账户创建成功！！请返回登录");
            }
            else
            {
                printf("register fail!\n");
            }
        }

    }
}


void register1::on_return_button_clicked()
{
    this->close();
    MainWindow *w = new MainWindow();
    w->setWindowTitle("Baackup Pack   -   登录");
    w->show();
}


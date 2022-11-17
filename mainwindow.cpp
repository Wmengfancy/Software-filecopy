//连接数据库以及登录功能

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap *pix = new QPixmap(":/blue.png");
    QSize sz = ui->label_image->size();
    ui->label_image->setPixmap(pix->scaled(sz));
    //设置图片阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(-3, 0);
    shadow->setColor(QColor("#888888"));
    shadow->setBlurRadius(30);
    ui->label_image->setGraphicsEffect(shadow);

    //connect(ui->login,SIGNAL(clicked()),this,SLOT(on_login_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_login_clicked()
{
    QString name_sql = ui->name1->text();
    QString password_sql = ui->password1->text();

    if(name_sql=="")
    QMessageBox::warning(this,"","用户名不能为空");
    else if (password_sql=="")
    QMessageBox::warning(this,"","密码不能为空");
    else{
        QString S = QString("select * from information where name='%1' and password = '%2' " ).arg(name_sql,password_sql);
        QSqlQuery query;
        query.exec(S);
        if(query.first())
        {
            QMessageBox::information(NULL, "登录通知", "登录成功！！");
            choose *cho = new choose();
            cho->show();
            connect(this,SIGNAL(sendData(QString)),cho,SLOT(getData(QString)));
            emit sendData(name_sql);
            this->close();
        }
        else
            QMessageBox::critical(this,"登录失败","用户名或密码错误，请重试！");
    }
}

void MainWindow::on_register_2_clicked()
{
    this->close();
    register1 *reg = new register1();
    reg->setWindowTitle("Baackup Pack   -   创建账户");
    reg->show();
}


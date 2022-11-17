#include "mainwindow.h"
#include "register1.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    qDebug()<<QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("wang22748");
    db.setDatabaseName("filecopy");
    if(!db.open())
    {
        qDebug()<<"error";
    }
    else
    {
        qDebug()<<"connect";
    }
    QSqlError error;
    error=db.lastError();
    if(error.isValid())//发生错误时isValid()返回true
    {
        switch (error.type()) {
            case QSqlError::NoError:
                qDebug()<<"无错误";
                break;
            case QSqlError::ConnectionError://连接错语
                qDebug()<<error.text();
                break;
            case QSqlError::StatementError://语句错语
                qDebug()<<error.text();
                break;
            case QSqlError::TransactionError://事务错误
                qDebug()<<error.text();
                break;
            default://未知错误
                qDebug()<<error.text();
                break;
        }
     }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

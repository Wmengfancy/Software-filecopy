#ifndef CHOOSE_H
#define CHOOSE_H

#include <QWidget>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <iostream>
#include <QApplication>
#include <QProcess>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <common.h>
#include "fileinfo.h"
#include "filecompressor.h"

#define DATA_FILE_NAME "DATA.BACKUP"
#define UNIT_FILE_NAME "UNIT.BACKUP"

struct FIleUnitInfo //文件元信息结构体
{
    off_t TotalLength;
    ino_t Inode;
    nlink_t InodeCount;
    FileType Type;
    short int Auth;
    timespec Atime;
    uid_t UserID;
    gid_t GroupID;
    off_t Size;
    off_t StartOffset;
    std::string RelativePath;
};

namespace Ui {
class choose;
}

class choose : public QWidget
{
    Q_OBJECT

public:
    explicit choose(QWidget *parent = nullptr);
    ~choose();

private slots:   
    void on_backup_clicked();
    void on_restore_clicked();
    void getData(QString);

private:
    Ui::choose *ui;
    QString name;
};

#endif // CHOOSE_H

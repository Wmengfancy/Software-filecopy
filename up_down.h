#ifndef UP_DOWN_H
#define UP_DOWN_H

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "mainwindow.h"

using namespace std;
/*
class up_down
{
public:
    up_down();
};
*/
struct historysend
{
    char id[17];
    char time[20];
    char path[129];
    char size[17];
};

int upload(const std::string &path,const std::string &name);
int download(const std::string &path_user,const std::string &package_path);
char *getFileName(char *path);
char *getTime();
size_t min(size_t a,size_t b);

#endif // UP_DOWN_H


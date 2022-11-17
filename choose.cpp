      
//该文件是选择备份还是恢复界面
//需要陈美化选择备份与恢复界面

#include "choose.h"
#include "filepacker.h"
#include "up_down.h"
#include "ui_choose.h"

using namespace std;

choose::choose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose)
{
    ui->setupUi(this);

    //connect(ui->restore,SIGNAL(clicked()),this,SLOT(on_restore_clicked()));
    //connect(ui->backup,SIGNAL(clicked()),this,SLOT(on_backup_clicked()));

}

choose::~choose()
{
    delete ui;
}

void choose::on_backup_clicked() //点击备份按钮
{
    QString fileName;

    //这一个QMessageBox的功能为选择备份目录还是文件
    //需要chen美化一下界面框与跳转之类的
    QMessageBox *messagebox  = new QMessageBox(this);
    messagebox->setBaseSize(600,300);
    messagebox->setWindowTitle("beifenxuanze:");
    messagebox->setText("file or directory?");
    QPushButton *file =messagebox->addButton("file",QMessageBox::RejectRole);
    QPushButton *dir = messagebox->addButton("directory",QMessageBox::AcceptRole);
    messagebox->exec();
    if(messagebox->clickedButton() == file)
        fileName = QFileDialog::getOpenFileName(this,"选择文件","/home/fancy");
    else if(messagebox->clickedButton() == dir)
        fileName = QFileDialog::getExistingDirectory(this,"open","/home/fancy");

    char t[] = "/tmp/BackupFile.XXXXXX";
    QString tempDirectory = mkdtemp(t);   //创建临时文件
    tempDirectory +="/";

    //get the backup_file
    if (!fileName.isEmpty()) {
       qDebug() << "this is the file name " << fileName;
    }
    if(fileName.back() == '/')
        fileName.left(fileName.size() - 1);
    int pos = fileName.lastIndexOf('/',fileName.size() - 2);
    QString relativePath = fileName.right(fileName.size() - pos - 1);
    QString rootDirectory = fileName.left(pos+1);

    //文件打包
    //需要陈添加正在打包中....消息框，就在这一行代码前添加就可以
    FilePacker Packer = FilePacker(tempDirectory.toStdString(),true); 
    delete InodeRecorder::inodeRecorderBackup;
    InodeRecorder::inodeRecorderBackup = new InodeRecorderBackup();
    FileInfo *fileInfo = new FileInfo(relativePath.toStdString(),&Packer,rootDirectory.toStdString());
    if (fileInfo->Backup() != NO_ERROR)
    {
        delete fileInfo;
        fileInfo = nullptr;
        printf("Packup failed!\n");
        return;
    }
    delete fileInfo;
    fileInfo = nullptr;
    Packer.Compact();
    //文件打包完成
    //需要陈添加文件打包消息框结束

    //文件压缩
    //需要陈添加正在压缩中....消息框，同上
    FileCompressor *fileCompressor = new FileCompressor(tempDirectory.toStdString(),Packer.BackupFile);    
    if(fileCompressor->Compress() != NO_ERROR)
    {
        delete fileCompressor;
        printf("Compress failed!\n");
        return;
    }
    //文件压缩完成
    //需要陈完成同打包相同的内容

    //文件上传
    //需要陈添加上传文件中....消息框，同上
    if(upload((tempDirectory + COMPRESSOR_FILE_NAME).toStdString().c_str(),name.toStdString().c_str()) == 1)
    {
        fileCompressor->DeleteFile();
        delete fileCompressor;
        Packer.DeleteFile();
        //需要陈添加备份成功消息框
        printf("ALL PACKUP PROCESS FINISHED SUCCESSFULLY!\n");
        system((string("rm -R ") + tempDirectory.toStdString()).c_str());
    }
    else
    {
        delete fileCompressor;
        printf("Backup failed! Because unknown error occurred on uploading.\n");
        /*
        此处为上传失败弹出的消息框
        需要陈修改下面三条语句为可视化界面
        printf("Backup failed! Because unknown error occurred on uploading.\n");
        printf("Backup File store in %s",tempDirectory);
        cerr << "You can copy backup file to another position to manually backup." << endl;    
        */
        printf("Backup failed! Because unknown error occurred on uploading.\n");
        printf("Backup File store in %s",tempDirectory);       
    }
}

void choose::on_restore_clicked()
{
    char tr[] = "/tmp/BackupToolTmpFile.XXXXXX";
    QString tempDirectory = mkdtemp(tr);
    tempDirectory += "/";

    //此处添加选择目录界面，并将所得目录传递给变量rootDirectory
    QString rootDirectory = QFileDialog::getExistingDirectory(this,"open","/home/fancy");
    if (!rootDirectory.isEmpty()) {
       qDebug() << "this is the file name " << rootDirectory;
    }
    if (rootDirectory.back() != '/')
            rootDirectory += '/';

    QString packDirecroty_user = "/home/fancy/packup/" + name;
    QString packDirectory = QFileDialog::getOpenFileName(this,"选择文件",packDirecroty_user);
    if (!packDirectory.isEmpty()) {
       qDebug() << "this is the file name " << packDirectory;
    }

    //需要陈添加下载文件中......消息框
    if(download(packDirectory.toStdString().c_str(),tempDirectory.toStdString().c_str())==1){ //下载备份的文件
    //需要陈 下载完成结束消息框

        //解压缩
        //需要陈添加解压文件中......消息框
        FileCompressor *fileCompressor = new FileCompressor(tempDirectory.toStdString());
        if(fileCompressor->Decompress() != NO_ERROR)
        {
            delete fileCompressor;
            printf("decompress failed!\n");
            return;
            //error
        }
        fileCompressor->DeleteFile();
        delete fileCompressor;
        //需要陈 解压完成结束消息框

        //解包
        //需要陈 添加正在解包中......消息框
        FilePacker Packer = FilePacker(tempDirectory.toStdString(),false);
        Packer.Disassemble();
        delete InodeRecorder::inodeRecorderRestore;
        InodeRecorder::inodeRecorderRestore = new InodeRecorderRestore();
        off_t ProcessBarTotal = Packer.UnitFile->Length();
        off_t ProcessBarCurrent{0};
        while(Packer.UnitFile->peek() != EOF)
        {
            FileInfo *fileInfo = new FileInfo(&Packer,rootDirectory.toStdString());
            if(fileInfo->Restore() != NO_ERROR)
            {
                delete fileInfo;
                fileInfo = nullptr;
                //添加恢复失败消息框
                printf("restore failed!\n");
                return;
                //error
            }
            char adjust = (ProcessBarCurrent>>20) & 0x1;
            ProcessBarCurrent = Packer.UnitFile->tellg();
            if(((ProcessBarCurrent>>20) & 0x1) == adjust + 1)
                //需要陈 添加恢复进度条（可选）
                cout << "\rRestoring: (" << ProcessBarCurrent << " / " << ProcessBarTotal << ")" << endl;
            delete fileInfo;
            fileInfo = nullptr;
        }
        //需要陈 解包结束消息框
        Packer.DeleteFile();
        cout << "Restoring: (" << ProcessBarTotal << " / " << ProcessBarTotal << ")" << endl;
        //需要陈添加恢复成功消息框
        cout << "All restore process finished successfully!" << endl;
        system((string("rm -R ") + tempDirectory.toStdString()).c_str());
    }
    else
    {
        //需要陈 添加恢复失败消息框，并说明是下载失败的原因，请再试一次，将下面的语句转化为可视化界面
        //printf("download fail!\n");
        //printf("Please try again\n");
        printf("download fail!\n");
        system((string("rm -R ") + tempDirectory.toStdString()).c_str());
    }
        
}

void choose::getData(QString str1)
{
    //获取从mainwindow界面登录成功的用户名
    name = str1;
}


    